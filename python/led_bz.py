

"""
led_bz.py

- 거리 정보 파일(/tmp/distance_fb.txt)을 읽어
- 전방/후방 중 더 위험한 거리 기준으로 상태 판단
- LED / Buzzer 제어 로직의 핵심 판단 부분만 정리

- 팀 프로젝트 Python 원본 코드에서 핵심 로직만 가져와서 포트폴리오용으로 정리한 코드입니다.
- 최종 프로젝트 구조에서는 사용되지 않았습니다.
"""

import os

DIST_FILE = "/tmp/distance_fb.txt"

def read_front_back():
    """전/후방 거리 값 파싱"""
    if not os.path.exists(DIST_FILE):
        return None, None

    front, back = None, None

    try:
        with open(DIST_FILE, "r") as f:
            for line in f:
                if line.startswith("F="):
                    front = float(line.split("=")[1])
                elif line.startswith("B="):
                    back = float(line.split("=")[1])
    except:
        return None, None

    return front, back


def danger_level(front, back):
    """
    전방/후방 거리 중 더 위험한 값 기준 판단
    반환값: "SAFE", "WARN", "DANGER", "CRITICAL"
    """
    if front is None or back is None:
        return "SAFE"

    f = front if front >= 0 else 9999.0
    b = back  if back  >= 0 else 9999.0
    danger = min(f, b)

    if 20 < danger <= 30:
        return "WARN"
    elif 10 < danger <= 20:
        return "DANGER"
    elif danger <= 10:
        return "CRITICAL"
    else:
        return "SAFE"
