FROM ubuntu:latest

WORKDIR /app

RUN apt-get update && apt-get upgrade -y && apt-get install -y \
    g++ \
    libcpprest-dev \
    libboost-all-dev \
    libssl-dev \
    cmake

RUN mkdir ./storage

RUN useradd -m -s /bin/bash appuser

# Важно: устанавливаем права на директорию ПОСЛЕ создания пользователя
RUN chown -R appuser:appuser ./storage

COPY main.cpp .
COPY .env .
COPY src/ .
COPY include/ .
COPY test/ ./test
COPY run.sh .

RUN chown appuser:appuser run.sh
RUN chmod 755 run.sh

RUN g++ -o main main.cpp -lcpprest -lboost_system -lboost_thread -lboost_chrono -lboost_random -lssl -lcrypto
RUN g++ -o test_main ./test/test_main.cpp -lboost_unit_test_framework

EXPOSE 8080

VOLUME ["/app/storage"]

USER appuser

CMD ["./run.sh"]