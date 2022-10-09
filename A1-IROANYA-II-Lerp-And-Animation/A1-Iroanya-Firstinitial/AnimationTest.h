#pragma once
#include "Obj.h"
#include<fstream>
#include<sstream>
#include <map>




class AnimationTest {
	vector<Obj*> objs;
public:
	AnimationTest() {
		
		std::ifstream file("animation.txt");
		if (file.is_open()) {
			std::string line;
			while (std::getline(file, line)) {

				string strs[20];
				Utils::splitString(strs, line);

				if (strs[0] == "OBJECT") {
					objs.push_back(new Obj(stoi(strs[1]), strs[2]));
				}
				else if (strs[0] == "KEYFRAME") {
					Obj* obj = getObj(stoi(strs[1]));
					if (obj == nullptr) {
						printf("Object %d does not exist\n" , stoi(strs[1]));
						continue;
					}
					int time = stoi(strs[2]);
					float positionX = stof(strs[3]);
					float positionY = stof(strs[4]);
					float positionZ = stof(strs[5]);

					float rotationX = stof(strs[6]);
					float rotationY = stof(strs[7]);
					float rotationZ = stof(strs[8]);

					float scaleX = stof(strs[9]);
					float scaleY = stof(strs[10]);
					float scaleZ = stof(strs[11]);
					KeyFrame keyFrame(time,positionX,positionY,positionZ,rotationX,rotationY,rotationZ,scaleX,scaleY,scaleZ);

					//  creative
					if (strs[12] != "") {
						keyFrame.r = stof(strs[12]);
					}
					if (strs[13] != "") {
						keyFrame.g = stof(strs[13]);
					}
					if (strs[14] != "") {
						keyFrame.b = stof(strs[14]);
					}
					if (strs[15] != "") {
						keyFrame.alpha = stof(strs[15]);
					}
					//

					if (obj->getKeyFrames().size() > 0 && time < obj->getKeyFrames()[obj->getKeyFrames().size() - 1].time) {
						printf("Object %d have keyframe error\n", stoi(strs[1]));
						continue;
					}
					obj->addKeyFrame(keyFrame);
				}
			}
			file.close();
		}
	}

	Obj* getObj(int id) {
		for (Obj* obj : objs) {
			if (obj->getId() == id) {
				return obj;
			}
		}
		return nullptr;
	}

	vector<Obj*> getObjs() {
		return objs;
	}

	Obj* getObjAtTime(int itime,int objId) {
		Obj* obj = objs.at(objId);

		for (int i = 0; i < obj->getKeyFrames().size() - 1; i++) {
			KeyFrame keyFrame = obj->getKeyFrames()[i];
			KeyFrame nextKeyFrame = obj->getKeyFrames()[i + 1];
			for (int time = keyFrame.time; time <= nextKeyFrame.time; time++) {
				float maxTime = nextKeyFrame.time - keyFrame.time;
				float curTime = time - keyFrame.time;
				float pX = Utils::lerp(keyFrame.positionX, nextKeyFrame.positionX, (float)curTime / (float)maxTime);
				float pY = Utils::lerp(keyFrame.positionY, nextKeyFrame.positionY, (float)curTime / (float)maxTime);
				float pZ = Utils::lerp(keyFrame.positionZ, nextKeyFrame.positionZ, (float)curTime / (float)maxTime);
				float rX = Utils::lerp(keyFrame.rotationX, nextKeyFrame.rotationX, (float)curTime / (float)maxTime);
				float rY = Utils::lerp(keyFrame.rotationX, nextKeyFrame.rotationX, (float)curTime / (float)maxTime);
				float rZ = Utils::lerp(keyFrame.rotationZ, nextKeyFrame.rotationZ, (float)curTime / (float)maxTime);
				float sX = Utils::lerp(keyFrame.scaleX, nextKeyFrame.scaleX, (float)curTime / (float)maxTime);
				float sY = Utils::lerp(keyFrame.scaleY, nextKeyFrame.scaleY, (float)curTime / (float)maxTime);
				float sZ = Utils::lerp(keyFrame.scaleZ, nextKeyFrame.scaleZ, (float)curTime / (float)maxTime);

				//creative
				float alpha = Utils::lerp(keyFrame.alpha, nextKeyFrame.alpha, (float)curTime / (float)maxTime);
				float r = Utils::lerp(keyFrame.r, nextKeyFrame.r, (float)curTime / (float)maxTime);
				float g = Utils::lerp(keyFrame.g, nextKeyFrame.g, (float)curTime / (float)maxTime);
				float b = Utils::lerp(keyFrame.b, nextKeyFrame.b, (float)curTime / (float)maxTime);

				if (itime == time) {
					obj->updateAtrr(pX, pY, pZ, rX, rY, rZ, sX, sY, sZ);
					obj->alpha = alpha; // creative
					obj->r = r; //creative
					obj->g = g; //creative
					obj->b = b; //creative
					break;
				}
			}
		}
		
		return obj;
	}

	void print() {
		for (Obj* obj : objs) {
			printf("Object: %d \n\n",obj->getId());

			for (int i = 0; i < obj->getKeyFrames().size() - 1;i++) {

				KeyFrame keyFrame = obj->getKeyFrames()[i];
				KeyFrame nextKeyFrame = obj->getKeyFrames()[i + 1];
				printf("\n");
				for (int time = keyFrame.time; time <= nextKeyFrame.time; time++) {
					float maxTime = nextKeyFrame.time - keyFrame.time;
					float curTime = time - keyFrame.time;

					printf("\t %.2f %.2f %.2f \t %.2f %.2f %.2f \t %.2f %.2f %.2f \n",
						Utils::lerp(keyFrame.positionX, nextKeyFrame.positionX, (float)curTime  / (float)maxTime),
						Utils::lerp(keyFrame.positionY, nextKeyFrame.positionY, (float)curTime	 / (float)maxTime),
						Utils::lerp(keyFrame.positionZ, nextKeyFrame.positionZ, (float)curTime	 / (float)maxTime),
						Utils::lerp(keyFrame.rotationX, nextKeyFrame.rotationX, (float)curTime	 / (float)maxTime),
						Utils::lerp(keyFrame.rotationX, nextKeyFrame.rotationX, (float)curTime	 / (float)maxTime),
						Utils::lerp(keyFrame.rotationZ, nextKeyFrame.rotationZ, (float)curTime	 / (float)maxTime),
						Utils::lerp(keyFrame.scaleX, nextKeyFrame.scaleX,		(float)curTime	 / (float)maxTime),
						Utils::lerp(keyFrame.scaleY, nextKeyFrame.scaleY,		(float)curTime	 / (float)maxTime),
						Utils::lerp(keyFrame.scaleZ, nextKeyFrame.scaleZ,		(float)curTime	 / (float)maxTime)
					);
				}
				printf("\n");
			}
		}
	}

	void test() {
		print();
	}

};