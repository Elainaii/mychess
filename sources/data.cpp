//
// Created by Elaina on 2023/12/9.
//
#include "chess.h"
#include "nlohmann/json.hpp"
#include "fstream"
//chessxy结构体
void to_json(nlohmann::json& j, const chessxy& p) {
	j = nlohmann::json{{"i", p.i_}, {"j", p.j_}, {"cur", p.currChess}, {"step", p.step}};
}

void from_json(const nlohmann::json& j, chessxy& p) {
	j.at("i").get_to(p.i_);
	j.at("j").get_to(p.j_);
	j.at("cur").get_to(p.currChess);
	j.at("step").get_to(p.step);
}

//chessData结构体
void to_json(nlohmann::json& j, const chessData& p) {
	j = nlohmann::json{{"id", p.id}, {"mode", p.mode}, {"totalStep", p.totalStep}, {"xy", p.xy_}, {"isEnd", p.isEnd}};
}

void from_json(const nlohmann::json& j, chessData& p) {
	j.at("id").get_to(p.id);
	j.at("mode").get_to(p.mode);
	j.at("totalStep").get_to(p.totalStep);
	j.at("xy").get_to(p.xy_);
	j.at("isEnd").get_to(p.isEnd);
}

void chess::save()
{
	if(step_ == 1)
	{
		//干嘛呢
		return;
	}
	chessData data0;
	if(data_.empty())
		data0 ={1,mode_,step_,xy_,isEnd_};
	else
		data0 ={data_.rbegin()->id + 1,mode_,step_,xy_,isEnd_};
	data_.push_back(data0);
	nlohmann::json j = data_;//将vector中存储的数据转换成json类型
	std::ofstream file("chessData.json");
	file << j.dump(4);  // 使用缩进为4的格式化输出
	file.close();
}

std::vector<chessData> chess::load()
{
	std::ifstream file("chessData.json");
	std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	// 将JSON数据解析为json对象
	nlohmann::json j;
	std::vector<chessData> data;
	if(!str.empty())
	{
		j = nlohmann::json::parse(str);
		data = j.get<std::vector<chessData>>();
	}
	// 将json对象转换为std::vector<chessData>对象
	data_ = data;
	return data;
}