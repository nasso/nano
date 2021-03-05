FROM nheuillet/docker-epitech-c AS build
WORKDIR /code
COPY . .
WORKDIR /code/build
RUN cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=/code/build && cmake --build .

FROM fedora:32
COPY --from=build /code/build/nanotekspice /bin/nanotekspice
ENTRYPOINT [ "/bin/nanotekspice" ]
