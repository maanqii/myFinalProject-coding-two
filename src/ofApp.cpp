#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //background
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(139,134,130,0);
    img.load("1.png");

    //GL_TEXTURE_2D for models coords.
    ofDisableArbTex(); 



    bAnimate = false;
    bAnimateMouse = false;
    animationPosition = 0;


    //download model and set up
    model.loadModel("1.dae", false);
    model.setPosition(ofGetWidth() * 0.6, (float)ofGetHeight() * 0.7 , 0);
    model.setScale(0.4, 0.4, 0.4);


    model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    model.playAllAnimations();
    if(!bAnimate) {
        model.setPausedForAllAnimations(true);
    }

    // load in sounds
    bgm.load("song.mp3");
    bgm.setVolume(0.5);
    bgm.play();
    
    bHelpText = true;


}

//--------------------------------------------------------------
void ofApp::update(){

    model.update();
    

    if(bAnimateMouse) {
        model.setPositionForAllAnimations(animationPosition);
    }

    mesh = model.getCurrentAnimatedMesh(0);


}

//--------------------------------------------------------------
void ofApp::draw(){

    //image
    img.draw(0, 0);


    ofSetColor(255);

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

	ofEnableDepthTest();



    //some model & light stuff
    //model effect
#ifndef TARGET_PROGRAMMABLE_GL
    glShadeModel(GL_SMOOTH); 
#endif

    light.enable();
    ofEnableSeparateSpecularLight();

  
    ofPushMatrix();
    ofTranslate(model.getPosition().x, model.getPosition().y, 0);
    ofRotateDeg(-mouseX, 0, 1, 0);
    ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);

    model.drawFaces();

    ofPopMatrix();


    //ofmesh effect
#ifndef TARGET_PROGRAMMABLE_GL
    glEnable(GL_NORMALIZE);
#endif

    ofPushMatrix();
    ofTranslate(model.getPosition().x, model.getPosition().y, 0);
    ofRotateDeg(-mouseX, 0, 1, 0);
    ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);


    ofxAssimpMeshHelper & meshHelper = model.getMeshHelper(0);

    ofMultMatrix(model.getModelMatrix());
    ofMultMatrix(meshHelper.matrix);


    //modify ofmesh with some noise😀
    float liquidness = 5;
    float amplitude = mouseY / 100.0;
    float speedDampen = 5;
    auto& verts = mesh.getVertices();

    for (unsigned int i = 0; i < verts.size(); i++) {
        verts[i].x += ofSignedNoise(verts[i].x / liquidness, verts[i].y / liquidness, verts[i].z / liquidness, ofGetElapsedTimef() / speedDampen) * amplitude;
        verts[i].y += ofSignedNoise(verts[i].z / liquidness, verts[i].x / liquidness, verts[i].y / liquidness, ofGetElapsedTimef() / speedDampen) * amplitude;
        verts[i].z += ofSignedNoise(verts[i].y / liquidness, verts[i].z / liquidness, verts[i].x / liquidness, ofGetElapsedTimef() / speedDampen) * amplitude;
    }



    ofMaterial & material = meshHelper.material;

    if(meshHelper.hasTexture()){
        meshHelper.getTextureRef().bind();
    }
    material.begin();
    mesh.drawWireframe();
    material.end();

    if(meshHelper.hasTexture()){
        meshHelper.getTextureRef().unbind();
    }
    ofPopMatrix();

    ofDisableDepthTest();
    light.disable();
    ofDisableLighting();
    ofDisableSeparateSpecularLight();

    if(bHelpText){
    ofSetColor(232,232,232);

    stringstream ss;
    ss <<"CULTURAL TOUR" << endl;
    ss << " " << endl;
    ss <<"Display of different antiques(keys 1-7)"<<endl;
    ss <<"Move the mouse up and down to change the ofmesh changes"<<endl;
    ss <<"Hide/Show instructions(key H)"<<endl;
    ofDrawBitmapString(ss.str().c_str(), 50, 50);

    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    glm::vec3 modelPosition(ofGetWidth() * 0.6, (float)ofGetHeight() * 0.7, 0);
    

    switch (key) {
        case '1':
            img.load("1.png");
            model.loadModel("1.dae");
            model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
            model.setScale(0.4, 0.4, 0.4);
            ofEnableSeparateSpecularLight();
            break;
        case '2':
            img.load("2.png");
            model.loadModel("2.dae");
            model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
            model.setScale(0.4, 0.4, 0.4);
            ofEnableSeparateSpecularLight();
            break;
        case '3':
            img.load("3.png");
            model.loadModel("8.dae");
            model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
            model.setScale(0.5, 0.5, 0.5);
            ofDisableSeparateSpecularLight();
            break;
        case '4':
            img.load("4.png");
            model.loadModel("4.dae");
            model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
            model.setScale(0.4, 0.4, 0.4);
            ofDisableSeparateSpecularLight();
            break;
		case '5':
            img.load("5.png");
			model.loadModel("5.dae");
		    model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
            model.setScale(0.3, 0.3, 0.3);
            ofDisableSeparateSpecularLight();
			break;
        case '6':
            img.load("4.png");
            model.loadModel("6.dae");
            model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
            model.setScale(0.4, 0.4, 0.4);
            ofDisableSeparateSpecularLight();
            break;
        case '7':
            img.load("7.png");
            model.loadModel("7.dae");
            model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
            model.setScale(0.3, 0.3, 0.3);
            ofDisableSeparateSpecularLight();
            break;
		case ' ':
			bAnimate = !bAnimate;
			break;
        case 'h':
            bHelpText = !bHelpText;
            break;
        default:
            break;
    }

	mesh = model.getMesh(0);

    model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    model.playAllAnimations();
    if(!bAnimate) {
        model.setPausedForAllAnimations(true);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
     //scrub through aninations manually.
	animationPosition = y / (float)ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // pause all animations, so we can scrub through them manually.
     model.setPausedForAllAnimations(true);
	 animationPosition = y / (float)ofGetHeight();
     bAnimateMouse = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

