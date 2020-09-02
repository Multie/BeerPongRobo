import { Component, OnInit, Input } from '@angular/core';
import { MyRobot, RobotService } from '../robot.service';

@Component({
  selector: 'app-robo-info',
  templateUrl: './robo-info.component.html',
  styleUrls: ['./robo-info.component.scss'],
})
export class RoboInfoComponent implements OnInit {

  @Input() content:MyRobot;
  robot:MyRobot;
  readonlyIp:boolean;

  constructor(private robotService:RobotService) { 
    this.robot = new MyRobot("");
  }

  ngOnInit() {
    if (this.content != null) {
      this.robot = this.content;
      this.readonlyIp =  this.robot.ip == "All"
    }
  }

  compareFn(a,b):boolean {
    return a==b;
  }

  send() {
    if (this.robot.ip == "All") {
      this.robotService.robots.forEach((element)=> {
        this.robotService.sendRobotData(element);
      });
    }
    else {
      this.robotService.sendRobotData(this.robot);
    }

  }

}
