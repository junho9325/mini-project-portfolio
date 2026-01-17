
/*
  sensor.c
  Raspberry Pi 4에서 초음파 센서(HC-SR04) 거리 측정
  측정된 거리를 Arduino로 시리얼 전송
  거리 구간에 따라 LED / Buzzer로 사용자 피드백 제공

  ※ 본 코드는 팀 프로젝트 원본 코드에서 핵심 로직(센서 측정 / 전송 / 상태 판단)만 가져와서
     포트폴리오용으로 정리한 코드입니다.
*/

/* [핵심 1] 초음파 거리 측정 */
float measure_distance(int trig, int echo) {
    gpioWrite(trig, 0);
    gpioDelay(2000);

    gpioWrite(trig, 1);
    gpioDelay(10);
    gpioWrite(trig, 0);

    // Echo 신호 HIGH 구간 시간 측정
    while (gpioRead(echo) == 0);
    uint32_t start = gpioTick();

    while (gpioRead(echo) == 1);
    uint32_t end = gpioTick();

    // 거리 계산 (cm)
    return (end - start) * 0.0343f / 2.0f;
}

/* [핵심 2] Arduino로 거리 값 전송
 * - dist: 측정된 거리 값 (cm)
 * - serial_fd: Arduino와 연결된 시리얼 파일 디스크립터
 */
char buf[32];
snprintf(buf, sizeof(buf), "%.2f\n", dist);
write(serial_fd, buf, strlen(buf));

/* [핵심 3] 거리 기반 LED / Buzzer 상태 제어
 * - gpioTick()을 사용해 delay 없이 주기 제어
*/
uint32_t now = gpioTick();

if (dist > 30.0f) {
    setLED(0, 0, 0);
    beep_interval = 0;
}
else if (dist > 20.0f) {
    setLED(0, 1, 0);
    beep_interval = 2000000;
}
else if (dist > 10.0f) {
    setLED(0, 0, 1);
    beep_interval = 1000000;
}
else {
    setLED(1, 0, 0);
    beep_interval = 500000;
}

// 부저 주기 제어 (논블로킹)
if (beep_interval > 0 && (now - last_beep_time) >= beep_interval) {
    beep();
    last_beep_time = now;
}

// 측정 주기 조절
gpioDelay(10000);
