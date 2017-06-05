#include "../include/Responses.h"


void Responses::add(int where,int what){
	responses[where] = what;

}
int Responses::getNumberOfTag(int t){
	return count_if(responses.begin(),responses.end(),[t](int i){ return i == t;});
}
int Responses::numberOfResponses(){
	return count_if(responses.begin(),responses.end(),[](int i){return i != -1;});
}
void Responses::print(){
	for(int i =0;i<responses.size();i++){
		cout<<responses[i]<<" ";
	}
	cout<<endl;
}
int Responses::getElem(int n){
	return responses[n];
};

int Responses::getSize(){
	return responses.size();
}
void Responses::clear(){
	responses = vector<int>(number,-1);
};