
# 초음파 센서 기반 장애물 회피 RC카 (Mini Project)
3일간 진행하는 미니 프로젝트로 Arduino + Raspberry Pi 기반 장애물 감지 RC카 입니다.

## 최종 구현 사진/영상
[링크](https://drive.google.com/drive/folders/1t4AsPlC0XhethQiueich9ddT3AVpEsqB)

## 프로젝트 개요
- 기간: 3일
- 인원: 4명 (팀 프로젝트)
- 목적: 초음파 센서를 이용한 장애물 감지 및 모터 제어를 통한 RC카 주행 구현


## 하드웨어
- Arduino UNO
- Raspberry Pi 4
- HC-SR04 초음파 센서
- DC Motor + L298N


## 소프트웨어 / 언어
- C: Raspberry Pi 초음파 거리 측정 및 Arduino로 데이터 전송
- Arduino: DC 모터 제어 및 주행 로직
- Python: LED/Buzzer 제어 로직 (최종 버전에선 미사용)


## 시스템 구성
- Raspberry Pi에서 초음파 센서를 통한 거리(cm)를 측정
- 측정된 거리 값을 시리얼 통신으로 Arduino로 통신
- Arduino는 수신된 거리 값 기준으로 전진 / 정지 판단
- LED / Buzzer는 거리 구간에 따른 시각, 청각으로 피드백

<img width="700" height="831" alt="구상도" src="https://github.com/user-attachments/assets/263b0f3e-3c43-413c-9fdc-e28ac9b3db36" />

## 담당 역할
- 조장으로 팀원들 의견 취합 및 역할 분배
- PPT 및 문서 작업 진행
- Arduino 기반 DC 모터 제어 로직 구현
- 거리 값에 따른 전진 / 정지 판단 설계
- Raspberry Pi 와 Arduino 간 통신 테스트


## 개발 과정
1. 초음파 센서 2개를 사용한 거리 측정 시도
2. 센서 값 튐 현상 및 모터 오동작 발생
3. FIFO 기반 Python 제어 시도
4. LED 및 Buzzer 동작되지만, 모터 제어 실패
5. 일정 부족으로 초음파 센서 1개 구조 및 Python 대신 C 통합 제어 구조로 단순화 진행


## 문제점 및 해결
- 문제1: 초음파 센서 2개를 사용 시 거리 값 불안정
- 원인: 동시 측정 시 타이밍 충돌
- 해결: 센서 축소 및 구조 단순화 진행

- 문제2: Python과 C 분리 제어 시 모터 미동작
- 해결: 시스템 구조 단순화를 위한 C 통합 제어로 구조 변경


## 실행 흐름
1. Raspberry Pi: 초음파 센서 거리 측정
2. 거리 값(cm)을 시리얼로 Arduino로 통신
3. Arduino: 거리 기준 주행 판단
  - 안전 거리 > 전진
  - 정지 거리 이하 > 정지
4. Raspberry Pi: 거리 기준에 따른 LED/Buzzer 제어
  - 안전 거리 > LED 초록빛, Buzzer 안울림
  - 설정한 거리 미만 및 정지 전 거리 > LED 파란색, Buzzer 1초마다 알림
  - 정지 거리 이하 > LED 빨간색, Buzzer 0.1초마다 알림
5. 통신 종료 시 정지

## 아쉬운 점
- 초음파 센서 2개를 이용하지 못한 부분
- Python과 C 동시 제어 못한 부분
