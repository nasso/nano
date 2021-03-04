FROM nheuillet/docker-epitech-c

WORKDIR /code
COPY . .

WORKDIR /code/build
RUN cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release

CMD [ "ctest" ]
