#include "shape.h"

////////////////////Shape Class ////////////////////

//Constructor
void shape::setLocation(float x,float y, float theta){
    this->x = x;        //Set location
    this->y = y;

    while (theta<0){
	theta = theta+360; //bring to right range
    }

    this->theta = theta/180*3.14159;    //Convert to radians
}	

////////////////////Line Class////////////////////
//Constructor
void line::setParams(float length){
    this->length = length;

    int N, i, j;            
    float thetaTemp;
    float x_increment, y_increment;
    float x_plot, y_plot;
    
    N = length*5;   //Number of points
    
    for (j =0 ; j<36; j++){
	    LUTx[j] =new float[N];      //Create LUT for angle
	    LUTy[j] =new float[N];

	    thetaTemp = 10.0*j/180*3.14159;

	    //Find increments
	    x_increment = length*cos(thetaTemp)/N;
	    y_increment = length*sin(thetaTemp)/N;
	    //Initiazl coordinates
	    x_plot = 0;
	    y_plot = 0;	

	    //Find coordinates and print
	    for (i = 0; i<N ;i++){
		LUTx[j][i] = x_plot;        //Store in LUT
		LUTy[j][i] = y_plot;
		x_plot= x_plot + x_increment;   //Calcualte new coordiantes
		y_plot= y_plot + y_increment;
	    }
    }


}

// draws an outline of the shape in the image passed in
// using greyscale color of value 80 to draw the pixels
void line::drawOutline(unsigned char *image,int width,int height){
    int thetaTemp = ((int)(theta*18/3.14159+0.5))%36; 

    int N, i, coordinate;

    N = length*5;   //Number of points

    //Find coordinates and print
    for (i = 0; i<N ;i++){
        coordinate = (int)(x+LUTx[thetaTemp][i] + 0.5) + (int)(y+LUTy[thetaTemp][i] + 0.5)*width;           //Calc coordinate
        image[coordinate]=80;       //Draw new pixel
    }
    
    
}

// check if shape can be placed at location (x,y) in the image
// after rotating it by theta degrees using criteria in Note (2)
bool line::isValidLocation(unsigned char *image,int width,int height){
    int thetaTemp = ((int)(theta*18/3.14159+0.5))%36; 

    int N, i, coordinate;
    int x_plot, y_plot;

    N = length*5;   //Number of points

    x_plot = (x+LUTx[thetaTemp][N-1] + 0.5);
    y_plot = (y+LUTy[thetaTemp][N-1] + 0.5);

    //Go through each point to print and check if obstacle
    for (i = 0; i<(N-1) ;i++){
        coordinate = x_plot + y_plot*width;   //Calculate index
        
        if(x_plot>=width||y_plot>=height||x_plot<0||y_plot<0) return false;     //Within bounds
        if (image[coordinate]==0) return false;             //Not obstacle

        x_plot = (x+LUTx[thetaTemp][i] + 0.5);      //caculate coordinate
        y_plot = (y+LUTy[thetaTemp][i] + 0.5);
    }
    
    return true;    //if no obstacle, return true
}

bool line::isValidLocationCorners(unsigned char *image,int width,int height){
    int thetaTemp = ((int)(theta*18/3.14159+0.5))%36; 

    int N, i, coordinate;
    int x_plot, y_plot;

    N = length*5;   //Number of points

    x_plot = (x+LUTx[thetaTemp][N-1] + 0.5);        //Last point
    y_plot = (y+LUTy[thetaTemp][N-1] + 0.5);        
    coordinate = x_plot + y_plot*width;

    if(x_plot>=width||y_plot>=height||x_plot<0||y_plot<0) return false;     //Within bounds
    if (image[coordinate]==0) return false;             //Not obstacle

    x_plot = (x+LUTx[thetaTemp][0] + 0.5);      //First Point
    y_plot = (y+LUTy[thetaTemp][0] + 0.5);        
    coordinate = x_plot + y_plot*width;
        
    if(x_plot>=width||y_plot>=height||x_plot<0||y_plot<0) return false;     //Within bounds
    if (image[coordinate]==0) return false;             //Not obstacle
    
    return true;    //if no obstacle, return true
}


////////////////////Arc Class////////////////////

//Constructor
void arc::setParams(float radius,float arc_angle){
    radius = radius;		//Correction factor
    this->radius = radius;
    this->arc_angle = arc_angle/180*3.14159;    //Convert to radians

    int N, i, j;
    float thetaTemp;
    float radian_increment, radians;
    float x_plot, y_plot;
    
    N = 5.0*arc_angle*radius;   //Number of points to calculate
    
    for (j =0 ; j<36; j++){
	    LUTx[j] =new float[N];	
	    LUTy[j] =new float[N];

	    thetaTemp = 10.0*j/180*3.14159;

	    //Find increments
	    radian_increment = arc_angle/N;
	    radians = thetaTemp;
	    //Initial coordinates
	    x_plot = 0;
	    y_plot = 0;
	    
	    //Find coordinates for each point and print
	    for (i = 0; i<N ;i++){
            LUTx[j][i] = radius*cos(radians);       //Calculate new coordinates
            LUTy[j][i] = radius*sin(radians);
            radians = radians + radian_increment;   //Find new angle
	    }
    }
}

// draws an outline of the shape in the image passed in
// using greyscale color of value 80 to draw the pixels
void arc::drawOutline(unsigned char *image,int width,int height){
    int thetaTemp = ((int)(theta*18/3.14159+0.5))%36; 

    int N, i, coordinate;

    N = 5.0*arc_angle*radius;   //Number of points to calculate

    //Find coordinates and print
    for (i = 0; i<N ;i++){
        coordinate = (int)(x+LUTx[thetaTemp][i] + 0.5) + ((int)(y+LUTy[thetaTemp][i] + 0.5))*width;
        image[coordinate]=80;       //Draw new pixel
    }
    
    
}

// check if shape can be placed at location (x,y) in the image
// after rotating it by theta degrees using criteria in Note (2)
bool arc::isValidLocation(unsigned char *image,int width,int height){
    int thetaTemp = ((int)(theta*18/3.14159+0.5))%36; 

    int N, i, coordinate;
    int x_plot, y_plot;

    N = 5.0*arc_angle*radius;   //Number of points to calculate

    x_plot = (x+LUTx[thetaTemp][N-1] + 0.5);
    y_plot = (y+LUTy[thetaTemp][N-1] + 0.5);

    //Go through each point to print and check if obstacle
    for (i = 0; i<(N-1) ;i++){
        coordinate = x_plot + y_plot*width;
        
        if(x_plot>=width||y_plot>=height||x_plot<0||y_plot<0) return false;     //Within bounds
        if (image[coordinate]==0) return false;             //Not obstacle

	x_plot = (x+LUTx[thetaTemp][i] + 0.5);
	y_plot = (y+LUTy[thetaTemp][i] + 0.5);
    }
    
    return true;    //if no obstacle, return true
}

bool arc::isValidLocationCorners(unsigned char *image,int width,int height){
    int thetaTemp = ((int)(theta*18/3.14159+0.5))%36; 

    int N, i, coordinate;
    int x_plot, y_plot;

    N = 5.0*arc_angle*radius;   //Number of points to calculate

    x_plot = (x+LUTx[thetaTemp][N-1] + 0.5);        //Last point
    y_plot = (y+LUTy[thetaTemp][N-1] + 0.5);        
    coordinate = x_plot + y_plot*width;

    if(x_plot>=width||y_plot>=height||x_plot<0||y_plot<0) return false;     //Within bounds
    if (image[coordinate]==0) return false;             //Not obstacle

    x_plot = (x+LUTx[thetaTemp][0] + 0.5);      //First point
    y_plot = (y+LUTy[thetaTemp][0] + 0.5);        
    coordinate = x_plot + y_plot*width;
        
    if(x_plot>=width||y_plot>=height||x_plot<0||y_plot<0) return false;     //Within bounds
    if (image[coordinate]==0) return false;             //Not obstacle
    
    x_plot = (x+LUTx[thetaTemp][(int)N/2] + 0.5);       //End point of circle
    y_plot = (y+LUTy[thetaTemp][(int)N/2] + 0.5);        
    coordinate = x_plot + y_plot*width;
        
    if(x_plot>=width||y_plot>=height||x_plot<0||y_plot<0) return false;     //Within bounds
    if (image[coordinate]==0) return false;             //Not obstacle

    return true;    //if no obstacle, return true
}

////////////////////Rhombus Class ////////////////////

void rhombus::setLocation(float x,float y, float theta){
    float newX, newY, newTheta;
    this->x = x;
    this->y = y;
    this->theta = theta/180*3.14159;    //Convert to radians
    
    //calcualte x, y, theta for each line and set location for lines
    newX = x;
    newY = y;
    newTheta = this->theta;
    top.setLocation(newX,newY,newTheta/3.14159*180);
    
    newX = newX+this->width*cos(newTheta);
    newY = newY+this->width*sin(newTheta);
    newTheta = this->theta + this->corner_angle;
    right.setLocation(newX,newY,newTheta/3.14159*180);
    
    newX = newX+this->height*cos(newTheta);
    newY = newY+this->height*sin(newTheta);
    newTheta = this->theta + 3.14159;
    bottom.setLocation(newX,newY,newTheta/3.14159*180);
    
    newX = newX+this->width*cos(newTheta);
    newY = newY+this->width*sin(newTheta);
    newTheta = this->theta + this->corner_angle + 3.14159;
    left.setLocation(newX,newY,newTheta/3.14159*180);
}

//Constructor
void rhombus::setParams(float width,float height, float corner_angle){
    this->height = height;
    this->width = width;
    this->corner_angle = corner_angle/180*3.14159;
    
    //Set parameters for lines
    top.setParams(width);
    right.setParams(height);
    bottom.setParams(width);
    left.setParams(height);
}

// draws an outline of the shape in the image passed in
// using greyscale color of value 80 to draw the pixels
void rhombus::drawOutline(unsigned char *image,int width,int height){
    //Draw each of the lines
    top.drawOutline(image, width, height);
    right.drawOutline(image, width, height);
    bottom.drawOutline(image, width, height);
    left.drawOutline(image, width, height);
}

// check if shape can be placed at location (x,y) in the image
// after rotating it by theta degrees using criteria in Note (2)
bool rhombus::isValidLocation(unsigned char *image,int width,int height){

    //Check Corners for validity
    if(!top.isValidLocationCorners(image, width, height)){
	return false;
    }
    if(!bottom.isValidLocationCorners(image, width, height)){
	return false;
    }
   
    //Check Rest for validity
    if(!top.isValidLocation(image, width, height)){
	return false;
    }
    if(!right.isValidLocation(image, width, height)){
	return false;
    }
    if(!bottom.isValidLocation(image, width, height)){
	return false;
    }
    if(!left.isValidLocation(image, width, height)){
	return false;
    }
    
    return true;
}

////////////////////Lens Class ////////////////////

void lens::setLocation(float x,float y, float theta){
    float separation, vX, vY;
    float newX, newY, newTheta;

    this->x = x;
    this->y = y;
    this->theta = theta/180*3.14159;    //Convert to radians
    
    //Calculate difference in x,y for 2 arcs
    separation = 2*arc_radius*cos(arc_angle/2);
    vX = separation*cos(this->theta+arc_angle/2);
    vY = separation*sin(this->theta+arc_angle/2);
    
    //Calculate x,y,theta for each arc and set location
    newX = x;
    newY = y;
    newTheta = this->theta;
    bottom.setLocation(newX,newY,newTheta/3.14159*180);
    
    newX = x +vX;
    newY = y + vY;
    newTheta = this->theta + 3.14159;
    top.setLocation(newX,newY,newTheta/3.14159*180);
}

void lens::setParams(float radius,float arc_angle){
    this->arc_radius = radius;
    this->arc_angle = arc_angle/180*3.14159;
    
    //Set arc parametrs
    bottom.setParams(arc_radius, arc_angle);
    top.setParams(arc_radius, arc_angle);
}

// draws an outline of the shape in the image passed in
// using greyscale color of value 80 to draw the pixels
void lens::drawOutline(unsigned char *image,int width,int height){
    //Draw Outlines
    bottom.drawOutline(image, width, height);
    top.drawOutline(image, width, height);
}

// check if shape can be placed at location (x,y) in the image
// after rotating it by theta degrees using criteria in Note (2)
bool lens::isValidLocation(unsigned char *image,int width,int height){
    //Check corners for validity
    if(!top.isValidLocationCorners(image, width, height)){
	return false;
    }
    if(!bottom.isValidLocationCorners(image, width, height)){
	return false;
    }
   
    //Check Rest for validity
    if(!top.isValidLocation(image, width, height)){
	return false;
    }
    if(!bottom.isValidLocation(image, width, height)){
	return false;
    }
    
    return true;
}

////////////////////Capsule Class ////////////////////

void capsule::setLocation(float x,float y, float theta){
    float newX, newY, newTheta;
    
    this->x = x;
    this->y = y;
    this->theta = theta/180*3.14159;    //Convert to radians
        
    //Calculate new x,y, theta for each segment of shape and set location
    newX = x;
    newY = y;
    newTheta = this->theta;
    top.setLocation(x,y,this->theta/3.14159*180);
    
    newX = x + this->width*cos(this->theta) - this->height*sin(this->theta);
    newY = y + this->width*sin(this->theta) + this->height*cos(this->theta);
    newTheta = this->theta + 3.14159;
    bottom.setLocation(newX,newY,newTheta/3.14159*180);
    
    newX = x + this->width*cos(this->theta) - this->height/2*sin(this->theta);
    newY = y + this->width*sin(this->theta) + this->height/2*cos(this->theta);
    newTheta = this->theta - 3.14159/2;
    left.setLocation(newX,newY,newTheta/3.14159*180);
    
    newX = x - this->height/2*sin(this->theta);
    newY = y + this->height/2*cos(this->theta);
    newTheta = this->theta + 3.14159/2;
    right.setLocation(newX,newY,newTheta/3.14159*180);
}

void capsule::setParams(float width,float height){
    this->height = height;
    this->width = width;
    
    //Set parameters for sides
    top.setParams(width);
    bottom.setParams(width);
    left.setParams(height/2, 180);
    right.setParams(height/2, 180);
    
}

// draws an outline of the shape in the image passed in
// using greyscale color of value 80 to draw the pixels
void capsule::drawOutline(unsigned char *image,int width,int height){
    //Draw each of the sides
    top.drawOutline(image, width, height);
    bottom.drawOutline(image, width, height);
    left.drawOutline(image, width, height);
    right.drawOutline(image, width, height);
    
}

// check if shape can be placed at location (x,y) in the image
// after rotating it by theta degrees using criteria in Note (2)
bool capsule::isValidLocation(unsigned char *image,int width,int height){
    //Check Corners for validity
    if(!top.isValidLocationCorners(image, width, height)){
	return false;
    }
    if(!bottom.isValidLocationCorners(image, width, height)){
	return false;
    }
   
    //Check Rest for validity
    if(!top.isValidLocation(image, width, height)){
	return false;
    }
    if(!right.isValidLocation(image, width, height)){
	return false;
    }
    if(!bottom.isValidLocation(image, width, height)){
	return false;
    }
    if(!left.isValidLocation(image, width, height)){
	return false;
    }
    
    return true;
}
