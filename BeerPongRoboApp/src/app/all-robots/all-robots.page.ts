import { Component, OnInit } from '@angular/core';
import { MyRobot } from '../robot.service';

@Component({
  selector: 'app-all-robots',
  templateUrl: './all-robots.page.html',
  styleUrls: ['./all-robots.page.scss'],
})
export class AllRobotsPage implements OnInit {

  robot:MyRobot;

  constructor() { 
    this.robot = new MyRobot("All");
  }

  ngOnInit() {
  }

  send() {
    
  }
}
