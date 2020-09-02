import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { IonicModule } from '@ionic/angular';

import { AllRobotsPage } from './all-robots.page';

describe('AllRobotsPage', () => {
  let component: AllRobotsPage;
  let fixture: ComponentFixture<AllRobotsPage>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ AllRobotsPage ],
      imports: [IonicModule.forRoot()]
    }).compileComponents();

    fixture = TestBed.createComponent(AllRobotsPage);
    component = fixture.componentInstance;
    fixture.detectChanges();
  }));

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
