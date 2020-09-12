import { Component, OnInit } from '@angular/core';
import { RobotService } from '../robot.service';

@Component({
  selector: 'app-settings',
  templateUrl: './settings.page.html',
  styleUrls: ['./settings.page.scss'],
})
export class SettingsPage implements OnInit {

  constructor(private robotService:RobotService) { }

  ngOnInit() {
  }

}
