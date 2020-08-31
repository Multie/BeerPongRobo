import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { IonicModule } from '@ionic/angular';

import { RobotPage } from './robot.page';

describe('RobotPage', () => {
  let component: RobotPage;
  let fixture: ComponentFixture<RobotPage>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ RobotPage ],
      imports: [IonicModule.forRoot()]
    }).compileComponents();

    fixture = TestBed.createComponent(RobotPage);
    component = fixture.componentInstance;
    fixture.detectChanges();
  }));

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
