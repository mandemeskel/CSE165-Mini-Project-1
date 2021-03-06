#include "App.h"


void invertColor( Polygon * poly ) {

    poly->upper_left.setR( abs( poly->upper_left.getR() - 1 ) );
    poly->upper_left.setG( abs( poly->upper_left.getG() - 1 ) );
    poly->upper_left.setB( abs( poly->upper_left.getB() - 1 ) );
    
    // std::cout << &poly->upper_left << std::endl;
    
}


App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    mx = 0.0;
    my = 0.0;
    this->mouse = Point( mx, my );
    Rect * rect;

    rect = new Rect( 
        -0.9, 0, 0.2, 0.3    
    );
    rect->setOnClick( &invertColor );
    this->addPolygon( rect );

    
    rect = new Rect( 
        0, 0, 0.1, 0.1    
    );
    rect->setOnClick( &invertColor );
    this->addPolygon( rect );

    rect = new Rect( 
        -0.9, -0.7, 0.3, 0.2    
    );
    rect->setOnClick( &invertColor );
    this->addPolygon( rect );

    
    rect = new Rect( 
        0.6, 0, 0.25, 0.25    
    );
    rect->setOnClick( &invertColor );
    this->addPolygon( rect );

    rect = new Rect( 
        0, -0.7, 0.5, 0.1    
    );
    rect->setOnClick( &invertColor );
    this->addPolygon( rect );

    
    rect = new Rect( 
        0, 0.9, 0.1, 0.5    
    );
    rect->setOnClick( &invertColor );
    this->addPolygon( rect );


    rect = new Rect( 
        -0.95, 0.95, 0.5, 0.5    
    );
    rect->setOnClick( &invertColor );
    this->addPolygon( rect );

    rect = new Rect( 
        0.45, 0.95, 0.5, 0.7    
    );
    rect->setOnClick( &invertColor );
    this->addPolygon( rect );

}

void App::addShape( Shape * shape ) {

    this->shapes.push_front( shape );

}

void App::addPolygon( Polygon * poly ) {

    // for click detection
    this->polygons.push_front( poly );
    // for drawing
    this->shapes.push_front( poly );

}

void App::draw() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Set Color
    glColor3d(1.0, 1.0, 1.0);
    
    // Draw some points
    glBegin(GL_POINTS);
    
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    
    glEnd();
    
    // Draw a yellow cross
    glColor3d(1.0, 1.0, 0.0);
    
    glBegin(GL_LINES);
    
    glVertex2f(mx - 0.05f, my);
    glVertex2f(mx + 0.05f, my);
    
    glVertex2f(mx, my - 0.05f);
    glVertex2f(mx, my + 0.05f);
    
    glEnd();

    // draw our shapes
    for( int n = 0; n < this->shapes.size(); n++ )
        this->shapes[n]->draw();
    
    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

void App::mouseDown(float x, float y){
    // Update app state
    mx = x;
    my = y;

    mouse.setX( x );
    mouse.setY( y );

    Polygon * poly;
    // detect if mouse clicked any rects
    for( int n = 0; n < this->polygons.size(); n++ ) {
        
        poly = this->polygons[n];
        if( poly->contains( mouse ) )
            poly->click( mouse );

    }
    
    
    // Redraw the scene
    redraw();
}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
    // Redraw the scene
    redraw();
}

void App::keyPress(unsigned char key) {
    if (key == 27){
        // Exit the app when Esc key is pressed
        exit(0);
    }
}
