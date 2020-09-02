import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { AllRobotsPage } from './all-robots.page';

const routes: Routes = [
  {
    path: '',
    component: AllRobotsPage
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule],
})
export class AllRobotsPageRoutingModule {}
