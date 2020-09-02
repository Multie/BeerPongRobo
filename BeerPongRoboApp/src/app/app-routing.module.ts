import { NgModule } from '@angular/core';
import { PreloadAllModules, RouterModule, Routes } from '@angular/router';

const routes: Routes = [
  {
    path: '',
    redirectTo: 'robots',
    pathMatch: 'full'
  },
  {
    path: 'robots',
    loadChildren: () => import('./robot/robot.module').then( m => m.RobotPageModule)
  },
  {
    path: 'all-robots',
    loadChildren: () => import('./all-robots/all-robots.module').then( m => m.AllRobotsPageModule)
  },  {
    path: 'settings',
    loadChildren: () => import('./settings/settings.module').then( m => m.SettingsPageModule)
  }


];

@NgModule({
  imports: [
    RouterModule.forRoot(routes, { preloadingStrategy: PreloadAllModules })
  ],
  exports: [RouterModule]
})
export class AppRoutingModule {}
