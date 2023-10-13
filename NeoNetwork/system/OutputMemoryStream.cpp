#include "OutputMemoryStream.h"
#include"NeoLog.h"
neo::system::OutputMemoryStream::OutputMemoryStream(const Buffer& buffer) : MemoryStream(buffer)
{
}

neo::system::OutputMemoryStream::OutputMemoryStream(char* buffer, const size_t& capacity):MemoryStream(buffer,capacity)
{
	
}

neo::system::OutputMemoryStream::OutputMemoryStream(const OutputMemoryStream& output):MemoryStream(output.mBuffer,output.mCapacity)
{
	mHead = output.mHead;
}

neo::system::OutputMemoryStream::~OutputMemoryStream()
{

}

bool neo::system::OutputMemoryStream::Write(const void* inData, size_t inByteSize)
{
	//���� Ȯ���Ѵ�.
	int32_t resultHead = mHead + static_cast<uint32_t>(inByteSize);
	if (resultHead > mCapacity)
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"buffer write overflow : head [%d], copy size [%d]\n"
			, mHead, inByteSize);
		return false;
	}
	//������ ���� �տ� ����
	std::memcpy(mBuffer + mHead, inData, inByteSize);
	//mHead�� �������� ���� ��Ͽ� ���
	mHead = resultHead;

	return true;
}
