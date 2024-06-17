#include<stdio.h>

int main(){
  float r,g,b;
  float rcal,gcal,bcal;
  printf("Enter r val: ");
  scanf("%f",&r);
  printf("Enter r val: ");
  scanf("%f",&g);
  printf("Enter r val: ");
  scanf("%f",&b);

  rcal = (r-0.0)/(255.0-0.0);
  gcal = (g-0.0)/(255.0-0.0);
  bcal = (b-0.0)/(255.0-0.0);
  
  
  printf("r :%f g:%f b: %f",rcal,gcal,bcal);
  return 0;
}
