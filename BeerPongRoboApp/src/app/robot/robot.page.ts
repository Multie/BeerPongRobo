import { Component, OnInit } from '@angular/core';
import { RobotService,MyRobot } from '../robot.service';

@Component({
  selector: 'app-robot',
  templateUrl: './robot.page.html',
  styleUrls: ['./robot.page.scss'],
})
export class RobotPage implements OnInit {

  constructor(private robotService:RobotService) { 
    this.robots = this.robotService.robots;
    console.log(this.robots);
  }

  robots:Array<MyRobot>;

  ngOnInit() {
   /* this.robotService.getGateway().then((gateway)=> {
      console.log("Gateway:" + gateway);
      this.robotService.scannRobots(gateway).then((list)=> {
        console.log("List");
        console.log(list);

      

      }).catch(error=> {
        console.log("error" + error);
      })
      //*/
  //  });
 //   this.robot.scannRobots();
  }

}
