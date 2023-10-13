//#pragma once
//#include"PacketID.h"
//
//
//class P_S_NOTIFY_PING
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_S_NOTIFY_PING;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int64_t);
//		return static_cast<int32_t>(size);
//	}
//
//	int64_t time;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(time);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(time);
//
//	}
//};
//
//class P_C_NOTIFY_PING
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_C_NOTIFY_PING;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int64_t);
//		return static_cast<int32_t>(size);
//	}
//
//	int64_t time;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(time);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(time);
//
//	}
//};
//
//class P_C_REQ_LOGIN
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_C_REQ_LOGIN;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int16_t) + (sizeof(wchar_t) * id.length()) + sizeof(int16_t) + (sizeof(wchar_t) * uuid.length());
//		return static_cast<int32_t>(size);
//	}
//
//	std::wstring id;
//	std::wstring uuid;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(id);
//		buffer.Write(uuid);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(id);
//		buffer.Read(uuid);
//
//	}
//};
//
//class P_C_NOTIFY_RESPAWN
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_C_NOTIFY_RESPAWN;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int16_t) + (sizeof(wchar_t) * id.length());
//		return static_cast<int32_t>(size);
//	}
//
//	std::wstring id;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(id);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(id);
//
//	}
//};
//
//class P_C_REQ_CHANNEL_REGISTER
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_C_REQ_CHANNEL_REGISTER;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int32_t) + sizeof(int16_t) + (sizeof(wchar_t) * id.length());
//		return static_cast<int32_t>(size);
//	}
//
//	int32_t channelID;
//	std::wstring id;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(channelID);
//		buffer.Write(id);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(channelID);
//		buffer.Read(id);
//
//	}
//};
//
//class P_S_RES_CHANNEL_REGISTER
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_S_RES_CHANNEL_REGISTER;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int32_t) + sizeof(int32_t) + sizeof(int16_t) + (sizeof(wchar_t) * msg.length());
//		return static_cast<int32_t>(size);
//	}
//
//	int32_t statusCode;
//	int32_t channelID;
//	std::wstring msg;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(statusCode);
//		buffer.Write(channelID);
//		buffer.Write(msg);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(statusCode);
//		buffer.Read(channelID);
//		buffer.Read(msg);
//
//	}
//};
//
//class P_C_NOTIFY_CHANNEL_UNREGISTER
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_C_NOTIFY_CHANNEL_UNREGISTER;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int32_t) + sizeof(int32_t);
//		return static_cast<int32_t>(size);
//	}
//
//	int32_t statusCode;
//	int32_t channelID;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(statusCode);
//		buffer.Write(channelID);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(statusCode);
//		buffer.Read(channelID);
//
//	}
//};
//
//class ChannelInfo
//{
//public:
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int16_t) + (sizeof(wchar_t) * name.length()) + sizeof(int32_t) + sizeof(int32_t);
//		return static_cast<int32_t>(size);
//	}
//	std::wstring name;
//	int32_t userCount;
//	int32_t channedId;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		buffer.Write(name);
//		buffer.Write(userCount);
//		buffer.Write(channedId);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(name);
//		buffer.Read(userCount);
//		buffer.Read(channedId);
//
//	}
//};
//
//class P_S_NOTIFY_CHANNEL_INFO
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_S_NOTIFY_CHANNEL_INFO;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int32_t);
//		for (int i = 0; i < channelDatas.size(); i++) {
//			size += channelDatas[i].GetSize();
//		}
//
//		return static_cast<int32_t>(size);
//	}
//
//	std::vector<ChannelInfo> channelDatas;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(static_cast<int32_t>(channelDatas.size()));
//		for (int i = 0; i < channelDatas.size(); i++) {
//			channelDatas[i].Serialize(buffer);
//		}
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		size = 0;
//		buffer.Read(size);
//		for (int i = 0; i < size; i++) {
//			ChannelInfo data;
//			data.Deserialize(buffer);
//			channelDatas.push_back(data);
//		}
//
//	}
//};
//
//class PVector3
//{
//public:
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(float) + sizeof(float) + sizeof(float);
//		return static_cast<int32_t>(size);
//	}
//	float x;
//	float y;
//	float z;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		buffer.Write(x);
//		buffer.Write(y);
//		buffer.Write(z);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(x);
//		buffer.Read(y);
//		buffer.Read(z);
//
//	}
//};
//
//class PVector2
//{
//public:
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(float) + sizeof(float);
//		return static_cast<int32_t>(size);
//	}
//	float x;
//	float y;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		buffer.Write(x);
//		buffer.Write(y);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(x);
//		buffer.Read(y);
//
//	}
//};
//
//class P_C_UPDATE_CHAR_POSITION
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_C_UPDATE_CHAR_POSITION;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += position.GetSize() + velocity.GetSize() + sizeof(float) + sizeof(int32_t);
//		return static_cast<int32_t>(size);
//	}
//
//	PVector3 position;
//	PVector2 velocity;
//	float speed;
//	int32_t animation;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		position.Serialize(buffer);
//		velocity.Serialize(buffer);
//		buffer.Write(speed);
//		buffer.Write(animation);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		position.Deserialize(buffer);
//		velocity.Deserialize(buffer);
//		buffer.Read(speed);
//		buffer.Read(animation);
//
//	}
//};
//
//class P_C_REQ_CHARACTER_REGISTER
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_C_REQ_CHARACTER_REGISTER;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int16_t) + (sizeof(wchar_t) * name.length()) + sizeof(int16_t) + position.GetSize();
//		return static_cast<int32_t>(size);
//	}
//
//	std::wstring name;
//	int16_t mapID;
//	PVector3 position;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(name);
//		buffer.Write(mapID);
//		position.Serialize(buffer);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(name);
//		buffer.Read(mapID);
//		position.Deserialize(buffer);
//
//	}
//};
//
//class P_S_RES_CHARACTER_REGISTER
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_S_RES_CHARACTER_REGISTER;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		for (int i = 0; i < players.size(); i++) {
//			size += sizeof(int16_t) + (sizeof(wchar_t) * players[i].length());
//		}
//		size += sizeof(int32_t) + sizeof(int16_t) + (sizeof(wchar_t) * mag.length());
//		return static_cast<int32_t>(size);
//	}
//
//	int32_t statusCode;
//	std::wstring mag;
//	std::vector<std::wstring> players;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(statusCode);
//		buffer.Write(mag);
//		buffer.Write(static_cast<int32_t>(players.size()));
//		for (int i = 0; i < players.size(); i++) {
//			buffer.Write(players[i]);
//		}
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(statusCode);
//		buffer.Read(mag);
//		size = 0;
//		buffer.Read(size);
//		for (int i = 0; i < size; i++) {
//			std::wstring data;
//			buffer.Read(data);
//			players.push_back(data);
//		}
//
//	}
//};
//
//class P_C_REQ_CHARACTER_MAP_UNREGISTER
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_C_REQ_CHARACTER_MAP_UNREGISTER;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int16_t) + sizeof(int16_t) + (sizeof(wchar_t) * id.length());
//		return static_cast<int32_t>(size);
//	}
//
//	int16_t mapID;
//	std::wstring id;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(mapID);
//		buffer.Write(id);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(mapID);
//		buffer.Read(id);
//
//	}
//};
//
//class P_S_NOTIFY_MONSTER_MAP_REGISTER
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_S_NOTIFY_MONSTER_MAP_REGISTER;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int16_t) + sizeof(int16_t) + (sizeof(wchar_t) * id.length());
//		return static_cast<int32_t>(size);
//	}
//
//	int16_t mapID;
//	std::wstring id;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(mapID);
//		buffer.Write(id);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(mapID);
//		buffer.Read(id);
//
//	}
//};
//
//class P_S_NOTIFY_MONSTER_MAP_UNREGISTER
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_S_NOTIFY_MONSTER_MAP_UNREGISTER;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int16_t) + sizeof(int16_t) + (sizeof(wchar_t) * id.length());
//		return static_cast<int32_t>(size);
//	}
//
//	int16_t mapID;
//	std::wstring id;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(mapID);
//		buffer.Write(id);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(mapID);
//		buffer.Read(id);
//
//	}
//};
//
//class P_S_NOTIFY_CHARACTER_MAP_UNREGISTER
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_S_NOTIFY_CHARACTER_MAP_UNREGISTER;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int16_t) + sizeof(int16_t) + (sizeof(wchar_t) * id.length());
//		return static_cast<int32_t>(size);
//	}
//
//	int16_t mapID;
//	std::wstring id;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(mapID);
//		buffer.Write(id);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(mapID);
//		buffer.Read(id);
//
//	}
//};
//
//class P_S_NOTIFY_CHARACTER_INFO
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_S_NOTIFY_CHARACTER_INFO;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int16_t) + (sizeof(wchar_t) * id.length());
//		return static_cast<int32_t>(size);
//	}
//
//	std::wstring id;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(id);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(id);
//
//	}
//};
//
//class CharPositionData
//{
//public:
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int16_t) + (sizeof(wchar_t) * name.length()) + position.GetSize() + veleocity.GetSize() + sizeof(float) + sizeof(int32_t);
//		return static_cast<int32_t>(size);
//	}
//	std::wstring name;
//	PVector3 position;
//	PVector2 veleocity;
//	float speed;
//	int32_t animation;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		buffer.Write(name);
//		position.Serialize(buffer);
//		veleocity.Serialize(buffer);
//		buffer.Write(speed);
//		buffer.Write(animation);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(name);
//		position.Deserialize(buffer);
//		veleocity.Deserialize(buffer);
//		buffer.Read(speed);
//		buffer.Read(animation);
//
//	}
//};
//
//class P_S_NOTIFY_CHAR_POSITION
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_S_NOTIFY_CHAR_POSITION;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int32_t);
//		for (int i = 0; i < charDatas.size(); i++) {
//			size += charDatas[i].GetSize();
//		}
//
//		return static_cast<int32_t>(size);
//	}
//
//	std::vector<CharPositionData> charDatas;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(static_cast<int32_t>(charDatas.size()));
//		for (int i = 0; i < charDatas.size(); i++) {
//			charDatas[i].Serialize(buffer);
//		}
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		size = 0;
//		buffer.Read(size);
//		for (int i = 0; i < size; i++) {
//			CharPositionData data;
//			data.Deserialize(buffer);
//			charDatas.push_back(data);
//		}
//
//	}
//};
//
//class P_C_NOTIFY_MAP_REGISTER
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_C_NOTIFY_MAP_REGISTER;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int32_t) + sizeof(bool) + sizeof(int16_t) + (sizeof(wchar_t) * name.length());
//		return static_cast<int32_t>(size);
//	}
//
//	int32_t mapID;
//	bool isRegister;
//	std::wstring name;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(mapID);
//		buffer.Write(isRegister);
//		buffer.Write(name);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(mapID);
//		buffer.Read(isRegister);
//		buffer.Read(name);
//
//	}
//};
//
//class P_C_REQ_ATTACK_EVENT
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_C_REQ_ATTACK_EVENT;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int16_t) + sizeof(int16_t) + sizeof(int16_t) + sizeof(int32_t) + sizeof(int16_t) + (sizeof(wchar_t) * attackObject.length()) + sizeof(int16_t) + (sizeof(wchar_t) * hitObject.length());
//		return static_cast<int32_t>(size);
//	}
//
//	int16_t mapID;
//	int16_t dir;
//	int16_t animation;
//	int32_t damage;
//	std::wstring attackObject;
//	std::wstring hitObject;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(mapID);
//		buffer.Write(dir);
//		buffer.Write(animation);
//		buffer.Write(damage);
//		buffer.Write(attackObject);
//		buffer.Write(hitObject);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(mapID);
//		buffer.Read(dir);
//		buffer.Read(animation);
//		buffer.Read(damage);
//		buffer.Read(attackObject);
//		buffer.Read(hitObject);
//
//	}
//};
//
//class P_S_RES_ATTACK_EVENT
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_S_RES_ATTACK_EVENT;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int32_t);
//		return static_cast<int32_t>(size);
//	}
//
//	int32_t x;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(x);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(x);
//
//	}
//};
//
//class P_S_NOTIFY_ATTACK_ANI_EVENT
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_S_NOTIFY_ATTACK_ANI_EVENT;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int16_t) + sizeof(int16_t) + sizeof(int16_t) + sizeof(int16_t) + (sizeof(wchar_t) * player.length());
//		return static_cast<int32_t>(size);
//	}
//
//	int16_t mapID;
//	int16_t dir;
//	int16_t animation;
//	std::wstring player;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(mapID);
//		buffer.Write(dir);
//		buffer.Write(animation);
//		buffer.Write(player);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(mapID);
//		buffer.Read(dir);
//		buffer.Read(animation);
//		buffer.Read(player);
//
//	}
//};
//
//class P_S_NOTIFY_ATTACK_EVENT
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_S_NOTIFY_ATTACK_EVENT;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int16_t) + (sizeof(wchar_t) * hitObject.length()) + sizeof(int32_t);
//		return static_cast<int32_t>(size);
//	}
//
//	std::wstring hitObject;
//	int32_t remainHP;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(hitObject);
//		buffer.Write(remainHP);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(hitObject);
//		buffer.Read(remainHP);
//
//	}
//};
//
//class MonsterInfo
//{
//public:
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(float) + sizeof(float) + sizeof(int32_t) + sizeof(int16_t) + (sizeof(wchar_t) * name.length());
//		return static_cast<int32_t>(size);
//	}
//	float x;
//	float y;
//	int32_t hp;
//	std::wstring name;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		buffer.Write(x);
//		buffer.Write(y);
//		buffer.Write(hp);
//		buffer.Write(name);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(x);
//		buffer.Read(y);
//		buffer.Read(hp);
//		buffer.Read(name);
//
//	}
//};
//
//class P_S_NOTIFY_MONSTER_INFO
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_S_NOTIFY_MONSTER_INFO;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int32_t);
//		for (int i = 0; i < monsterDatas.size(); i++) {
//			size += monsterDatas[i].GetSize();
//		}
//		size += sizeof(int32_t) + sizeof(int16_t) + (sizeof(wchar_t) * msg.length());
//		return static_cast<int32_t>(size);
//	}
//
//	int32_t monsterCode;
//	std::wstring msg;
//	std::vector<MonsterInfo> monsterDatas;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(monsterCode);
//		buffer.Write(msg);
//		buffer.Write(static_cast<int32_t>(monsterDatas.size()));
//		for (int i = 0; i < monsterDatas.size(); i++) {
//			monsterDatas[i].Serialize(buffer);
//		}
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(monsterCode);
//		buffer.Read(msg);
//		size = 0;
//		buffer.Read(size);
//		for (int i = 0; i < size; i++) {
//			MonsterInfo data;
//			data.Deserialize(buffer);
//			monsterDatas.push_back(data);
//		}
//
//	}
//};
//
//class MonsterData
//{
//public:
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int16_t) + (sizeof(wchar_t) * name.length()) + position.GetSize() + veleocity.GetSize() + sizeof(float) + sizeof(int32_t);
//		return static_cast<int32_t>(size);
//	}
//	std::wstring name;
//	PVector3 position;
//	PVector2 veleocity;
//	float speed;
//	int32_t animation;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		buffer.Write(name);
//		position.Serialize(buffer);
//		veleocity.Serialize(buffer);
//		buffer.Write(speed);
//		buffer.Write(animation);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(name);
//		position.Deserialize(buffer);
//		veleocity.Deserialize(buffer);
//		buffer.Read(speed);
//		buffer.Read(animation);
//
//	}
//};
//
//class P_S_NOTIFY_MONSTER_POSITION
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_S_NOTIFY_MONSTER_POSITION;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int32_t);
//		for (int i = 0; i < monsterDatas.size(); i++) {
//			size += monsterDatas[i].GetSize();
//		}
//
//		return static_cast<int32_t>(size);
//	}
//
//	std::vector<MonsterData> monsterDatas;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(static_cast<int32_t>(monsterDatas.size()));
//		for (int i = 0; i < monsterDatas.size(); i++) {
//			monsterDatas[i].Serialize(buffer);
//		}
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		size = 0;
//		buffer.Read(size);
//		for (int i = 0; i < size; i++) {
//			MonsterData data;
//			data.Deserialize(buffer);
//			monsterDatas.push_back(data);
//		}
//
//	}
//};
//
//class P_S_NOTIFY_CHAR_UPDATE
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_S_NOTIFY_CHAR_UPDATE;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t);
//		return static_cast<int32_t>(size);
//	}
//
//	int32_t hp;
//	int32_t exp;
//	int32_t level;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(hp);
//		buffer.Write(exp);
//		buffer.Write(level);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(hp);
//		buffer.Read(exp);
//		buffer.Read(level);
//
//	}
//};
//
//class P_S_NOTIFY_EFFECT_EVENT
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_S_NOTIFY_EFFECT_EVENT;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += startPos.GetSize() + sizeof(int16_t) + (sizeof(wchar_t) * attackUser.length()) + sizeof(float) + sizeof(int16_t);
//		return static_cast<int32_t>(size);
//	}
//
//	PVector3 startPos;
//	std::wstring attackUser;
//	float dis;
//	int16_t dir;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		startPos.Serialize(buffer);
//		buffer.Write(attackUser);
//		buffer.Write(dis);
//		buffer.Write(dir);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		startPos.Deserialize(buffer);
//		buffer.Read(attackUser);
//		buffer.Read(dis);
//		buffer.Read(dir);
//
//	}
//};
//
//class P_C_REQ_ATTACK_RANGE_EVENT
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_C_REQ_ATTACK_RANGE_EVENT;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += startPos.GetSize() + sizeof(int16_t) + sizeof(int16_t) + sizeof(float) + sizeof(int32_t) + sizeof(int32_t) + sizeof(int16_t) + (sizeof(wchar_t) * attackUser.length());
//		return static_cast<int32_t>(size);
//	}
//
//	PVector3 startPos;
//	int16_t mapID;
//	int16_t dir;
//	float dis;
//	int32_t damage;
//	int32_t animation;
//	std::wstring attackUser;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		startPos.Serialize(buffer);
//		buffer.Write(mapID);
//		buffer.Write(dir);
//		buffer.Write(dis);
//		buffer.Write(damage);
//		buffer.Write(animation);
//		buffer.Write(attackUser);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		startPos.Deserialize(buffer);
//		buffer.Read(mapID);
//		buffer.Read(dir);
//		buffer.Read(dis);
//		buffer.Read(damage);
//		buffer.Read(animation);
//		buffer.Read(attackUser);
//
//	}
//};
//
//class P_C_REQ_ATTACK_RANGE_HIT_EVENT
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_C_REQ_ATTACK_RANGE_HIT_EVENT;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int16_t) + sizeof(int32_t) + sizeof(int16_t) + (sizeof(wchar_t) * attackUser.length()) + sizeof(int16_t) + (sizeof(wchar_t) * hitObject.length());
//		return static_cast<int32_t>(size);
//	}
//
//	int16_t mapID;
//	int32_t damage;
//	std::wstring attackUser;
//	std::wstring hitObject;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(mapID);
//		buffer.Write(damage);
//		buffer.Write(attackUser);
//		buffer.Write(hitObject);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(mapID);
//		buffer.Read(damage);
//		buffer.Read(attackUser);
//		buffer.Read(hitObject);
//
//	}
//};
//
//class P_C_REQ_LOGOUT
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_C_REQ_LOGOUT;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int16_t) + sizeof(int16_t) + (sizeof(wchar_t) * user.length());
//		return static_cast<int32_t>(size);
//	}
//
//	int16_t mapID;
//	std::wstring user;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(mapID);
//		buffer.Write(user);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(mapID);
//		buffer.Read(user);
//
//	}
//};
//
//class P_S_RES_LOGOUT
//	: public Packet {
//public:
//	PacketID GetID() {
//		return PacketID::PI_S_RES_LOGOUT;
//	}
//	int32_t GetSize() {
//		size_t size = 0;
//		size += sizeof(int16_t) + (sizeof(wchar_t) * user.length());
//		return static_cast<int32_t>(size);
//	}
//
//	std::wstring user;
//
//
//	void Serialize(OutputMemoryStream& buffer) {
//		HeaderSerialize(buffer);
//		buffer.Write(user);
//
//	}
//
//	void Deserialize(InputMemoryStream& buffer) {
//		int32_t size = 0;
//		buffer.Read(user);
//
//	}
//};
//
