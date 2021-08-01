
#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofNoFill();

	this->radius = 180;
	for (int deg = 0; deg < 360; deg += 1) {

		auto location = glm::vec2(this->radius * cos(deg * DEG_TO_RAD), this->radius * sin(deg * DEG_TO_RAD));
		this->base_location_list.push_back(location);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	this->log_list.clear();

	for (int i = 0; i < this->base_location_list.size(); i++) {

		vector<glm::vec3> log;
		log.push_back(glm::vec3(this->base_location_list[i], 0));
		this->log_list.push_back(log);
	}

	int step = 2;
	for (int i = 0; i < this->log_list.size(); i++) {

		while (this->log_list[i].size() < 120) {

			auto deg = ofMap(ofNoise(glm::vec4(this->log_list[i].back() * 0.015, (ofGetFrameNum() + this->log_list[i].size()) * 0.001)), 0, 1, -360, 360);
			auto tmp_1 = this->log_list[i].back() + glm::vec2(50 * cos(deg * DEG_TO_RAD), 50 * sin(deg * DEG_TO_RAD));
			auto tmp_deg = ofRandom(0, 360);
			auto tmp_2 = tmp_1 + glm::vec2(10 * cos(tmp_deg * DEG_TO_RAD), 10 * sin(tmp_deg * DEG_TO_RAD));
			auto next = this->log_list[i].back() + glm::normalize(tmp_2 - this->log_list[i].back()) * step;

			//auto next = this->log_list[i].back() + glm::vec2(step * cos(deg * DEG_TO_RAD), step * sin(deg * DEG_TO_RAD));
			this->log_list[i].push_back(next);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	ofSetColor(239, 39, 39);
	for (int i = 0; i < this->log_list.size(); i++) {

		ofBeginShape();
		ofVertices(this->log_list[i]);
		ofEndShape();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}