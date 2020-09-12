import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})
export class RobotService {

  robots: Array<MyRobot>;
  gateway: string;
  constructor(private http: HttpClient) {
    this.robots = [];
  }

  getGateway(): Promise<any> {
    return new Promise<any>((resolve) => {
      for (let a = 0; a < 256; a++) {
        this.http.get('http://192.168.' + a + '.1/', { responseType: 'text' }).subscribe((res) => {
          this.gateway = '192.168.' + a + ".";
          resolve('192.168.' + a + ".");


        }, (error) => {
        });
      }

    });
  }

  scannRobots(gateway) {
    return new Promise<Array<string>>((resolve, reject) => {
      if (!gateway.includes("192.168")) {
        console.log("no Gateway");
        reject("no Gateway");
      }
      var list = [];
      for (let a = 0; a < 256; a++) {
        this.http.get('http://' + gateway + a + '/robot', { responseType: 'text' }).subscribe((res) => {
          this.robots.push(new MyRobot(gateway + a));
          list.push(gateway + a);
        }, (error) => {

        });
      }
      resolve(list);
    });
  }

  getRobotData() {
    this.robots.forEach(robot => {
      this.http.get('http://' + robot.ip + '/', ).subscribe((res:MyRobot) => {
          robot = res;
        }, (error) => {

        });
    });
  }

  sendRobotData(robot: MyRobot) {
    var keys = Object.keys(robot)
    keys.forEach(key => {
      if (key != "ip" && key != "WifiIsHost") {
        this.http.post("http://" + robot.ip + "/" + key, robot[key]).subscribe((value) => {
        }, (error) => { });
      }
    });
  }

}


export class MyRobot {

  ip: string;

  TrackWhite: boolean;
  MotorMode: number;
  MotorStep: number;
  RobotSpeed: number;
  Mode1Forward: number;
  Mode2Rotate: number;
  LedMode: number;
  LedR: number;
  LedG: number;
  LedB: number;
  WifiIsHost: boolean;

  constructor(ip: string) {
    this.ip = ip;
    this.TrackWhite = false;
    this.MotorMode = 0;
    this.MotorStep = 0.1;
    this.RobotSpeed = 10;
    this.Mode1Forward = 0;
    this.Mode2Rotate = 0;
    this.LedMode = 0;
    this.LedR = 0;
    this.LedG = 0;
    this.LedB = 0;
    this.WifiIsHost = false;
  }



}