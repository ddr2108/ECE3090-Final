#include <math.h>

/////////////Generic Shape Class ///////////////////////
class shape{

protected:
	float x, y;
	float theta;		


public:
	
	//Set location
	virtual void setLocation(float x,float y, float theta);

	// draws an outline of the shape in the image passed in
	// using greyscale color of value 80 to draw the pixels
	virtual void drawOutline(unsigned char *image,int width,int height) = 0;

	// check if shape can be placed at location (x,y) in the image
	// after rotating it by theta degrees using criteria in Note (2)	
	virtual bool isValidLocation(unsigned char *image,int width,int height) = 0;

};

//////////////////Arc Class ///////////////////////////
class arc: public shape{
	float arc_angle;        //Arc parameters
	float radius;
    
	float* LUTx[36];        ///LUT for points
	float* LUTy[36];

public:
	//Constructor
	void setParams(float radius,float arc_angle);

	// draws an outline of the shape in the image passed in
	// using greyscale color of value 80 to draw the pixels
	void drawOutline(unsigned char *image,int width,int height);
    
	// check if shape can be placed at location (x,y) in the image
	// after rotating it by theta degrees using criteria in Note (2)
    bool isValidLocation(unsigned char *image,int width,int height);

    //Check for corners quickly
    bool isValidLocationCorners(unsigned char *image,int width,int height);

};

/////////////////Line Class//////////////////////////////
class line: public shape{
	float length;   //line parameters
    
	float* LUTx[36];        //Look up table
	float* LUTy[36];

public:
	//Constructor
	void setParams(float length);

	// draws an outline of the shape in the image passed in
	// using greyscale color of value 80 to draw the pixels
	void drawOutline(unsigned char *image,int width,int height);

	// check if shape can be placed at location (x,y) in the image
	// after rotating it by theta degrees using criteria in Note (2)	
    bool isValidLocation(unsigned char *image,int width,int height);

    //Check for corners quickly
    bool isValidLocationCorners(unsigned char *image,int width,int height);

};

class rhombus: public shape{
	float height;               //Rhombus parameters
	float width;
	float corner_angle;
    
	line left, right, top, bottom;      //Component of shape


public:
    //Set location of shape
    void setLocation(float x,float y, float theta);

	//set shape paraemters
	void setParams(float width,float height, float corner_angle);

	// draws an outline of the shape in the image passed in
	// using greyscale color of value 80 to draw the pixels
	void drawOutline(unsigned char *image,int width,int height);

	// check if shape can be placed at location (x,y) in the image
	// after rotating it by theta degrees using criteria in Note (2)	
    bool isValidLocation(unsigned char *image,int width,int height);

};

////////////////////Lens Class /////////////////////////////
class lens: public shape{
	
	float arc_radius;       //shape parameters
	float arc_angle;
    
    arc top, bottom;        //Sub shapes

public:
    //Set location of shape
    void setLocation(float x,float y, float theta);

    //set shape paraemters
	void setParams(float radius,float arc_angle);

	// draws an outline of the shape in the image passed in
	// using greyscale color of value 80 to draw the pixels
	void drawOutline(unsigned char *image,int width,int height);

	// check if shape can be placed at location (x,y) in the image
	// after rotating it by theta degrees using criteria in Note (2)	
    bool isValidLocation(unsigned char *image,int width,int height);

};


///////////////Capsule Class//////////////////////////
class capsule: public shape{
	float width;        //Shape parameters
	float height;
	
    line top, bottom;   //Sub shapes
    arc left, right;

public:
    //Set location of shape
    void setLocation(float x,float y, float theta);

    //set shape parameters
	void setParams(float width,float height);

	// draws an outline of the shape in the image passed in
	// using greyscale color of value 80 to draw the pixels
	void drawOutline(unsigned char *image,int width,int height);

	// check if shape can be placed at location (x,y) in the image
	// after rotating it by theta degrees using criteria in Note (2)	
    bool isValidLocation(unsigned char *image,int width,int height);

};
