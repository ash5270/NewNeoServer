using System;
using System.Collections.Generic;
using neo.system;
namespace neo::packet::game {
public class P_C_NOTIFY_PING
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_C_NOTIFY_PING;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int64) ;
		return size;
	}
	public Int64 time;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(time);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out time);

	}
};

public class P_C_NOTIFY_RTT
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_C_NOTIFY_RTT;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int64) ;
		return size;
	}
	public Int64 time;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(time);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out time);

	}
};

public class P_S_NOTIFY_PING
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_NOTIFY_PING;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int64) ;
		return size;
	}
	public Int64 time;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(time);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out time);

	}
};

public class P_S_NOTIFY_RTT
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_NOTIFY_RTT;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int64) ;
		return size;
	}
	public Int64 time;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(time);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out time);

	}
};

public class PlayerData
  {
	public Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + sizeof(Int32) + sizeof(Int16) + (sizeof(Int16) * name.Length) + sizeof(Int32) + sizeof(Int32) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(Int32) + sizeof(Int32) + sizeof(Int32) + sizeof(Int32) + uuid.Length ;
		return size;
	}
	public Int32 characterId;
	public Int32 mapId;
	public string name;
	public Int32 characterImageId;
	public Int32 characterWeaponId;
	public float posX;
	public float posY;
	public float velocityX;
	public float velocityY;
	public Int32 animaionCode;
	public Int32 Level;
	public Int32 Hp;
	public Int32 MaxHP;
	public byte[] uuid =new byte[16];
	

	public void Serialize(OutputMemoryStream buffer){
		buffer.Write(characterId);
		buffer.Write(mapId);
		buffer.Write(name);
		buffer.Write(characterImageId);
		buffer.Write(characterWeaponId);
		buffer.Write(posX);
		buffer.Write(posY);
		buffer.Write(velocityX);
		buffer.Write(velocityY);
		buffer.Write(animaionCode);
		buffer.Write(Level);
		buffer.Write(Hp);
		buffer.Write(MaxHP);
		buffer.Write(uuid, uuid.Length);

	}
	public void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out characterId);
		buffer.Read(out mapId);
		buffer.Read(out name);
		buffer.Read(out characterImageId);
		buffer.Read(out characterWeaponId);
		buffer.Read(out posX);
		buffer.Read(out posY);
		buffer.Read(out velocityX);
		buffer.Read(out velocityY);
		buffer.Read(out animaionCode);
		buffer.Read(out Level);
		buffer.Read(out Hp);
		buffer.Read(out MaxHP);
		buffer.Read(ref uuid, uuid.Length);

	}
};

public class PlayerPosData
  {
	public Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + sizeof(Int32) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(Int32) ;
		return size;
	}
	public Int32 characterId;
	public Int32 mapId;
	public float posX;
	public float posY;
	public float velocityX;
	public float velocityY;
	public Int32 animaionCode;
	

	public void Serialize(OutputMemoryStream buffer){
		buffer.Write(characterId);
		buffer.Write(mapId);
		buffer.Write(posX);
		buffer.Write(posY);
		buffer.Write(velocityX);
		buffer.Write(velocityY);
		buffer.Write(animaionCode);

	}
	public void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out characterId);
		buffer.Read(out mapId);
		buffer.Read(out posX);
		buffer.Read(out posY);
		buffer.Read(out velocityX);
		buffer.Read(out velocityY);
		buffer.Read(out animaionCode);

	}
};

public class P_C_UPDATE_CHAR_POSITION
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_C_UPDATE_CHAR_POSITION;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += playerPosition.GetSize() + uuid.Length ;
		return size;
	}
	public PlayerPosData playerPosition = new PlayerPosData();
	public byte[] uuid =new byte[16];
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		playerPosition.Serialize(buffer);
		buffer.Write(uuid, uuid.Length);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		playerPosition.Deserialize(buffer);
		buffer.Read(ref uuid, uuid.Length);

	}
};

public class P_S_NOTIFY_CHAR_POSITION
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_NOTIFY_CHAR_POSITION;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size+=sizeof(Int32);
		for(int i=0; i<playerPosition.Count; i++){
			size+= playerPosition[i].GetSize();
		}
		
		return size;
	}
	public List<PlayerPosData> playerPosition = new List<PlayerPosData>();
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write((int)(playerPosition.Count));
		for(int i=0; i<playerPosition.Count; i++){
			playerPosition[i].Serialize(buffer);
		}

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		size = 0;
		buffer.Read(out size);
		for(int i=0; i<size; i++){
			PlayerPosData data = new PlayerPosData();
			data.Deserialize(buffer);
			playerPosition.Add(data);
		}

	}
};

public class P_C_REQ_WORLD_ENTER_THE_SERVER
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_C_REQ_WORLD_ENTER_THE_SERVER;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + uuid.Length ;
		return size;
	}
	public Int32 characterId;
	public byte[] uuid =new byte[16];
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(characterId);
		buffer.Write(uuid, uuid.Length);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out characterId);
		buffer.Read(ref uuid, uuid.Length);

	}
};

public class P_S_RES_WORLD_PLAYER_DATA
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_WORLD_PLAYER_DATA;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += playerData.GetSize() ;
		return size;
	}
	public PlayerData playerData = new PlayerData();
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		playerData.Serialize(buffer);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		playerData.Deserialize(buffer);

	}
};

public class P_S_RES_WORLD_CHARACTERS
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_WORLD_CHARACTERS;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size+=sizeof(Int32);
		for(int i=0; i<playerDatas.Count; i++){
			size+= playerDatas[i].GetSize();
		}
		
		return size;
	}
	public List<PlayerData> playerDatas = new List<PlayerData>();
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write((int)(playerDatas.Count));
		for(int i=0; i<playerDatas.Count; i++){
			playerDatas[i].Serialize(buffer);
		}

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		size = 0;
		buffer.Read(out size);
		for(int i=0; i<size; i++){
			PlayerData data = new PlayerData();
			data.Deserialize(buffer);
			playerDatas.Add(data);
		}

	}
};

public class P_S_RES_WORLD_MONSTERS
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_WORLD_MONSTERS;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size+=sizeof(Int32);
		for(int i=0; i<playerDatas.Count; i++){
			size+= playerDatas[i].GetSize();
		}
		
		return size;
	}
	public List<PlayerData> playerDatas = new List<PlayerData>();
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write((int)(playerDatas.Count));
		for(int i=0; i<playerDatas.Count; i++){
			playerDatas[i].Serialize(buffer);
		}

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		size = 0;
		buffer.Read(out size);
		for(int i=0; i<size; i++){
			PlayerData data = new PlayerData();
			data.Deserialize(buffer);
			playerDatas.Add(data);
		}

	}
};

public class P_S_CLOSE_WORLD
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_CLOSE_WORLD;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) ;
		return size;
	}
	public Int32 characterId;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(characterId);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out characterId);

	}
};

public class P_S_NOTIFY_LEAVE_WORLD_PLAYER
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_NOTIFY_LEAVE_WORLD_PLAYER;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) ;
		return size;
	}
	public Int32 characterId;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(characterId);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out characterId);

	}
};

public class P_C_REQ_LEAVE_MAP
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_C_REQ_LEAVE_MAP;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + sizeof(Int32) + sizeof(Int32) + uuid.Length ;
		return size;
	}
	public Int32 leaveMapId;
	public Int32 enterMapId;
	public Int32 characterId;
	public byte[] uuid =new byte[16];
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(leaveMapId);
		buffer.Write(enterMapId);
		buffer.Write(characterId);
		buffer.Write(uuid, uuid.Length);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out leaveMapId);
		buffer.Read(out enterMapId);
		buffer.Read(out characterId);
		buffer.Read(ref uuid, uuid.Length);

	}
};

public class P_S_RES_ENTER_MAP
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_ENTER_MAP;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(float) + sizeof(float) + sizeof(Int32) ;
		return size;
	}
	public float posX;
	public float posY;
	public Int32 enterMapId;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(posX);
		buffer.Write(posY);
		buffer.Write(enterMapId);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out posX);
		buffer.Read(out posY);
		buffer.Read(out enterMapId);

	}
};

public class P_S_REQ_DB_ENTER_INGAME_CHAR_DATA
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_REQ_DB_ENTER_INGAME_CHAR_DATA;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + sizeof(Int32) + sizeof(Int32) ;
		return size;
	}
	public Int32 sessionId;
	public Int32 characterId;
	public Int32 channelId;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(characterId);
		buffer.Write(channelId);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out sessionId);
		buffer.Read(out characterId);
		buffer.Read(out channelId);

	}
};

public class P_S_RES_DB_ENTER_INGAME_CHAR_DATA
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_DB_ENTER_INGAME_CHAR_DATA;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + sizeof(Int32) + sizeof(Int16) + (sizeof(Int16) * characterName.Length) + sizeof(Int32) + sizeof(Int32) + sizeof(Int32) + sizeof(float) + sizeof(float) + sizeof(Int32) + sizeof(Int32) + sizeof(Int32) + sizeof(Int32) ;
		return size;
	}
	public Int32 sessionId;
	public Int32 mapId;
	public string characterName;
	public Int32 characterId;
	public Int32 characterImageId;
	public Int32 characterWeaponId;
	public float posX;
	public float posY;
	public Int32 animaionCode;
	public Int32 Level;
	public Int32 Hp;
	public Int32 MaxHP;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(mapId);
		buffer.Write(characterName);
		buffer.Write(characterId);
		buffer.Write(characterImageId);
		buffer.Write(characterWeaponId);
		buffer.Write(posX);
		buffer.Write(posY);
		buffer.Write(animaionCode);
		buffer.Write(Level);
		buffer.Write(Hp);
		buffer.Write(MaxHP);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out sessionId);
		buffer.Read(out mapId);
		buffer.Read(out characterName);
		buffer.Read(out characterId);
		buffer.Read(out characterImageId);
		buffer.Read(out characterWeaponId);
		buffer.Read(out posX);
		buffer.Read(out posY);
		buffer.Read(out animaionCode);
		buffer.Read(out Level);
		buffer.Read(out Hp);
		buffer.Read(out MaxHP);

	}
};

public class WorldMapData
  {
	public Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + sizeof(Int16) + (sizeof(Int16) * name.Length) + sizeof(Int32) + sizeof(Int32) ;
		return size;
	}
	public Int32 id;
	public string name;
	public Int32 monsterCode;
	public Int32 monsterCount;
	

	public void Serialize(OutputMemoryStream buffer){
		buffer.Write(id);
		buffer.Write(name);
		buffer.Write(monsterCode);
		buffer.Write(monsterCount);

	}
	public void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out id);
		buffer.Read(out name);
		buffer.Read(out monsterCode);
		buffer.Read(out monsterCount);

	}
};

public class P_S_REQ_DB_WORLD_MAP_INFO
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_REQ_DB_WORLD_MAP_INFO;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) ;
		return size;
	}
	public Int32 sessionId;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(sessionId);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out sessionId);

	}
};

public class P_S_RES_DB_WORLD_MAP_INFO
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_DB_WORLD_MAP_INFO;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size+=sizeof(Int32);
		for(int i=0; i<worldMapDatas.Count; i++){
			size+= worldMapDatas[i].GetSize();
		}
		
		return size;
	}
	public List<WorldMapData> worldMapDatas = new List<WorldMapData>();
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write((int)(worldMapDatas.Count));
		for(int i=0; i<worldMapDatas.Count; i++){
			worldMapDatas[i].Serialize(buffer);
		}

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		size = 0;
		buffer.Read(out size);
		for(int i=0; i<size; i++){
			WorldMapData data = new WorldMapData();
			data.Deserialize(buffer);
			worldMapDatas.Add(data);
		}

	}
};

}
