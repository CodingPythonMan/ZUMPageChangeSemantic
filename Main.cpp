#include "Network.h"
#include "Game.h"
#include "Log.h"

#pragma comment(lib, "winmm.lib")

#define WAIT 20

int main()
{
	// 타이머 해상도 높이기
	timeBeginPeriod(1);
	LogFileInit();

	//LoadData();
	Network network;

	network.StartUp();

	unsigned int tick = 0;
	unsigned int curTime = timeGetTime();
	unsigned int ourTime = curTime;
	unsigned int frameTime = curTime;
	int Frame = 0;
	while (Shutdown == false)
	{
		network.IOProcess();

		// 업데이트는 게임의 로직
		// 로직 처리
		//Update();

		// 키보드 입력을 통해서 서버를 제어할 경우 사용
		ServerControl();

		// 모니터링 정보를 표시, 저장, 전송하는 경우 사용
		// Monitor();

		// 프레임 계산 필요
		Frame++;

		curTime = timeGetTime();
		if (curTime - frameTime >= 1000)
		{
			_LOG(LOG_LEVEL_DEBUG, L"Frame : %d", Frame);
			Frame = 0;
			frameTime = curTime;
		}
		tick = curTime - ourTime;
		ourTime += WAIT;

		if (tick <= WAIT)
		{
			Sleep(WAIT - tick);
		}
	}

	// 서버 종료 대기
	
	// 서버는 함부로 종료해도 안된다.
	// DB에 저장할 데이터나 기타 마무리 할 일들이 모두 끝났는지 확인한 뒤 쓴다.


	return 0;
}