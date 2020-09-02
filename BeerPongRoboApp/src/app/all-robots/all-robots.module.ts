import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

import { IonicModule } from '@ionic/angular';

import { AllRobotsPageRoutingModule } from './all-robots-routing.module';

import { AllRobotsPage } from './all-robots.page';
import { RoboInfoComponent } from '../robo-info/robo-info.component';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    AllRobotsPageRoutingModule
  ],
  declarations: [AllRobotsPage,RoboInfoComponent]
})
export class AllRobotsPageModule {}
