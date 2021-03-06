import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

import { IonicModule } from '@ionic/angular';

import { RobotPageRoutingModule } from './robot-routing.module';

import { RobotPage } from './robot.page';
import { BrowserModule } from '@angular/platform-browser';
import { RoboInfoComponent } from '../robo-info/robo-info.component';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    RobotPageRoutingModule
  ],
  declarations: [RobotPage,RoboInfoComponent]
})
export class RobotPageModule {}
