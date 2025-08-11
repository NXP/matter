import { Component, ElementRef, AfterViewInit, ViewChild } from '@angular/core';
import { GetRequestsService } from '../../services/get-requests.service';
import { AppDialogService } from '../../services/app-dialog.service';
import { LoaderService } from './../../services/loader.service';
import { MatIcon } from '@angular/material/icon';
import * as d3 from 'd3';

interface NodeDatum extends d3.SimulationNodeDatum {
  id: string;
  deviceType: 'Root device' | 'Node device';
  deviceName: string;
  nodeAlias: string;
  nodeId: string;
  networkType?: string;
}

interface LinkDatum extends d3.SimulationLinkDatum<NodeDatum> {
  source: string | NodeDatum;
  target: string | NodeDatum;
}

@Component({
  selector: 'app-networkgraph',
  standalone: true,
  imports: [ MatIcon ],
  templateUrl: './networkgraph.component.html',
  styleUrls: ['./networkgraph.component.css'],
})
export class NetworkgraphComponent{

  @ViewChild('svgContainer', { static: true }) svgRef!: ElementRef<SVGSVGElement>;
  
  nodes: NodeDatum[] = [];

  constructor(private getRequestsService: GetRequestsService, private appDialogService: AppDialogService, private loaderService: LoaderService) {
  }

  ngAfterViewInit(): void {
    this.onPressedNetworkRefreshButton()
  }

  ngOnInit(): void {}

  ngOnDestroy(): void {}

  public onPressedNetworkRefreshButton() {
    this.loaderService.showLoader()
    try {
      this.nodes = [];
      this.getRequestsService.getNetwork().subscribe(
        (data: any) => {
          console.log("Parsed data: " + JSON.stringify(data))
          const parsedData = JSON.parse(JSON.stringify(data))
    
          if (parsedData['result'] === 'successful') {
            // Add root node
            this.nodes.push({
              id: '0',
              deviceType: 'Root device',
              deviceName: parsedData.machine || 'Unknown device',
              nodeAlias: '',
              nodeId: '',
              networkType: ''
            });
            if (parsedData['nodeList'] != null) {
              parsedData.nodeList.forEach((node: any, index: number) => {
                this.nodes.push({
                  id: (index + 1).toString(),
                  deviceType: 'Node device',
                  deviceName: '',
                  nodeAlias: node.nodeAlias || '',
                  nodeId: node.nodeId || '',
                  networkType: node.networkType || ''
                });
              });
            }
            // Add nodeList node
            console.log(this.nodes);
            this.loaderService.hideLoader()
            console.log("Hiding loader...")
            this.drawGraph();
          } else {
            this.loaderService.hideLoader()
            console.log("Hiding loader...")
            this.appDialogService.showErrorDialog('Failed to get network graph data');
          }
        }, (error: any) => {
          console.error('Error received: ', error);
          this.appDialogService.showErrorDialog('Error getting network graph data');
          this.loaderService.hideLoader();
          console.log("Hiding loader...")
        });
    } catch (error : any){
      this.loaderService.hideLoader()
      console.log("Hiding loader...")
      console.log("Got error while getting network graph data: " + error.toString())
    }
  }

  drawGraph(): void {
    const svg = d3.select(this.svgRef.nativeElement);
    svg.selectAll("*").remove();
    const boundingRect = this.svgRef.nativeElement.getBoundingClientRect();
    const width = boundingRect.width;
    const height = boundingRect.height;

    const links: LinkDatum[] = this.nodes
      .filter((node) => node.id !== '0')
      .map((node) => ({ source: '0', target: node.id }));

    const colorMap: Record<string, string> = {
      Root: '#834ab4',
      Thread: '#fca600',
      Ethernet: '#0eafe0',
      WiFi: '#69ca00',
      Unknow: '#9E9E9E',
      Offline: '#455A64',
    };

    const simulation = d3
      .forceSimulation<NodeDatum>(this.nodes)
      .force('link', d3.forceLink<NodeDatum, LinkDatum>(links).id((d) => d.id).distance(120))
      .force('charge', d3.forceManyBody().strength(-300))
      .force('center', d3.forceCenter(width / 2, height / 2));

    const link = svg
      .append('g')
      .attr('stroke', '#999')
      .selectAll('line')
      .data(links)
      .enter()
      .append('line')
      .attr('stroke-width', 2);

    const nodeGroup = svg
      .append('g')
      .selectAll('g')
      .data(this.nodes)
      .enter()
      .append('g')
      .call(
        d3
          .drag<SVGGElement, NodeDatum>()
          .on('start', (event, d) => {
            if (!event.active) simulation.alphaTarget(0.3).restart();
            d.fx = d.x;
            d.fy = d.y;
          })
          .on('drag', (event, d) => {
            d.fx = event.x;
            d.fy = event.y;
          })
          .on('end', (event, d) => {
            if (!event.active) simulation.alphaTarget(0);
            d.fx = null;
            d.fy = null;
          })
      );

    nodeGroup
      .append('circle')
      .attr('r', (d) => (d.id === '0' ? 30 : 25))
      .attr('fill', (d) => (colorMap[d.deviceType === 'Root device' ? 'Root' : (d.networkType ?? 'Unknow')] || '#9E9E9E'))
      .attr('stroke', '#fff')
      .attr('stroke-width', 1.5);
  
    nodeGroup
      .append('text')
      .text((d) => d.deviceName ? d.deviceName : d.nodeAlias)
      .attr('x', 0)
      .attr('y', (d) => (d.id === '0' ? 40 : 30))
      .attr('text-anchor', 'middle')
      .attr('font-size', '10px')
      .attr('font-family', 'Times New Roman')
      .attr('fill', '#333');

    simulation.on('tick', () => {
      link
        .attr('x1', (d: any) => d.source.x)
        .attr('y1', (d: any) => d.source.y)
        .attr('x2', (d: any) => d.target.x)
        .attr('y2', (d: any) => d.target.y);

      nodeGroup.attr('transform', (d: any) => `translate(${d.x},${d.y})`);
    });

    // Tooltip div
    const container = d3.select('#networkgraph-container');

    container.selectAll('.d3-tooltip').remove();

    const tooltip = container
      .append('div')
      .attr('class', 'd3-tooltip')
      .style('visibility', 'hidden');

    // Show tooltip on click
    nodeGroup.on('click', (event, d) => {
      event.stopPropagation();
      tooltip
        .html(`
          <strong>Device Type:</strong> ${d.deviceType}<br>
          <strong>Device Name:</strong> ${d.deviceName}<br>
          <strong>Node Alias:</strong> ${d.nodeAlias}<br>
          <strong>Node ID:</strong> ${d.nodeId}<br>
          <strong>Network Type:</strong> ${d.networkType}
        `)
        .style('top', `${event.pageY + 10}px`)
        .style('left', `${event.pageX + 10}px`)
        .style('visibility', 'visible');
    });

    // Hide tooltip on background click
    svg.on('click', () => {
      tooltip.style('visibility', 'hidden');
    });

    // Legend
    const legendData = Object.entries(colorMap).map(([label, color]) => ({ label, color }));
    const legend = svg.append('g').attr('transform', `translate(${width - 80}, 10)`);

    const legendItems = legend
      .selectAll('.legend-item')
      .data(legendData)
      .enter()
      .append('g')
      .attr('class', 'legend-item')
      .attr('transform', (_, i) => `translate(0, ${i * 25})`);

    legendItems
      .append('rect')
      .attr('width', 18)
      .attr('height', 18)
      .attr('fill', (d) => d.color);

    legendItems
      .append('text')
      .attr('x', 25)
      .attr('y', 13)
      .text((d) => d.label)
      .attr('font-size', '12px')
      .attr('font-family', 'Times New Roman')
      .attr('fill', '#333');
  }
}
