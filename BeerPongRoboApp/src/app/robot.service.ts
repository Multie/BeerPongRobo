import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})
export class RobotService {

  robots:Array<MyRobot>;
  gateway:string;
  constructor(private http: HttpClient ) { 
    this.robots = [
      new MyRobot("192.168.0.1")
    ];
  }

  getGateway():Promise<any> {
    return new Promise<any>((resolve)=> {
      for (let a = 0;a < 256;a++) {
        this.http.get('http://192.168.'+ a +'.1/',{responseType:'text'}).subscribe( (res)=> {
          this.gateway = '192.168.'+ a + ".";
          resolve('192.168.'+ a + ".");
          console.log("test");
        
        } , (error)=>{
        });
      }
      
    });
  }

  scannRobots(gateway) {
    return new Promise<Array<string>>((resolve,reject)=> {
      if (!gateway.includes("192.168")) {
        console.log("no Gateway");
        reject("no Gateway");
      }
      var list = [];
      for (let a = 0; a < 256; a++) {
        this.http.get('http://' +gateway+ a+'/robot',{responseType:'text'}).subscribe( (res)=> {
          this.robots.push(new MyRobot(gateway+ a));
          list.push(gateway+ a);
        } , (error)=>{
        
        });
      }
      resolve(list);
    });
  }

}


export class MyRobot {
  ip:string;
  red:number;
  green:number;
  blue:number;
  mode:number;
  power:boolean;
  ledMode:number;
  trackwhite:number;
  constructor(ip:string) {
    this.ip = ip;
  }
}