#pragma once


namespace neo::task
{
	//Task->
	//어떠한 일을 할 데이터 
	enum class TASK_TYPE
	{
		DEFAULT = 0,
		PACKET = 1,
	};

	class ITask
	{
	private:
		TASK_TYPE mType;
	protected:

	public:
		//
		
		//
		virtual  void Run();
		virtual  void Stop();
	};

	class PacketTask : public ITask
	{
		
	public:
		PacketTask();
		~PacketTask();

		void Run() override;
		void Stop() override;
	};



}


