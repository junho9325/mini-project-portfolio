
/*
  motor_control.ino
  Arduino UNO 모터 제어 핵심 로직
  거리 값에 따라 전진/정지 판단
  통신이 끊기면 TIMEOUT_MS 이후 정지
*/


void loop() {
  // 통신된 데이터가 있다면
  if (Serial.available() > 0)
  {
    distance = Serial.parseFloat();  // 초음파 거리값 저장
    lastReceiveTime = millis();      // 데이터 수신 시간 갱신

    // 장애물 거리 값이 0 이상일 때
    if (distance > 0)
    {
      if (distance < STOP_DIST)  
      {
        stopMotor();
      }
      else
      {
        forwardMove();
      }
    }
  }
  else
  {
    // 시리얼 데이터가 없고, 마지막 수신 후 1초 이상 경과 시 정지
    if (millis() - lastReceiveTime > TIMEOUT_MS)
    {
      stopMotor();
    }
  }
}

