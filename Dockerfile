# 사용할 베이스 이미지 선택
FROM ubuntu:20.04

# 작업 디렉토리 설정
WORKDIR /usr/src/app

RUN echo $(date +"%Y-%d-%m %H:%M:%S+%Z")

RUN apt update
RUN apt-get install -y software-properties-common

# 필요한 라이브러리 설치
RUN add-apt-repository ppa:pistache+team/unstable
RUN apt update
RUN apt-get install -y g++ make cmake libcpprest-dev
RUN apt install libpistache-dev -y

# 필요한 파일 복사
COPY main.cpp .

# C++ 소스 컴파일 및 실행 파일 생성
RUN g++ -std=c++17 -o main main.cpp -lpistache -pthread

# 포트 설정
EXPOSE 8080

# 컨테이너 실행 시 실행할 명령
CMD ["./main"]
