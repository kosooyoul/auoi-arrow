# 빌드용 베이스 이미지 선택
FROM ubuntu:20.04 as staged

# 작업 디렉토리 설정
WORKDIR /usr/src/app

# 빌드 패키지 설치
RUN apt-get update
RUN apt-get install -y g++ make cmake

# 필요한 라이브러리 저장소 설정
RUN apt-get install -y software-properties-common
RUN add-apt-repository ppa:pistache+team/unstable
RUN apt-get update

# 필요한 라이브러리 설치
RUN apt-get install -y libcpprest-dev
RUN apt-get install -y libpistache-dev

# 몽고DB 라이브러리
# RUN apt-get install -y pkg-config libmongoc-1.0-0 libmongoc-dev
# RUN apt-get install -y libmongoc-1.0-0 libbson-1.0-0
RUN apt-get install -y pkg-config libmongoc-dev

# 필요한 파일 복사
COPY ./src/ .

# C++ 소스 컴파일 및 실행 파일 생성
RUN g++ -std=c++17 -o main ./main.cpp ./*/*.cpp ./*/*/*.cpp -lpistache -pthread $(pkg-config --libs --cflags libmongoc-1.0)

# 운영용 베이스 이미지 선택
FROM ubuntu:20.04 as completed

# 작업 디렉토리 설정
WORKDIR /usr/src/app

# 빌드 및 라이브러리 복사
COPY --from=staged /usr/src/app ./
COPY --from=staged /usr/lib/aarch64-linux-gnu/*.so* /usr/lib/aarch64-linux-gnu/

# 포트 설정
EXPOSE 60000

# 컨테이너 실행 시 실행할 명령
# CMD ["./main"]
ENTRYPOINT ["./main"]
