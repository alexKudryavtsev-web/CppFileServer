FROM ubuntu:latest

WORKDIR /app

RUN apt-get upgrade
RUN apt-get update && apt-get install -y \
    g++ \
    libcpprest-dev \
    libboost-all-dev \
    libssl-dev \
    cmake

RUN mkdir ./storage

COPY main.cpp .
COPY .env .
COPY src/ .
COPY include/ .

RUN g++ -o main main.cpp -lcpprest -lboost_system -lboost_thread -lboost_chrono -lboost_random -lssl -lcrypto

EXPOSE 8080

VOLUME ["/app/storage"]

CMD ["./main"]