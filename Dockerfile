FROM emscripten/emsdk as build_nts
WORKDIR /app
COPY libnts .
WORKDIR /app/build
RUN emcmake cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=/app/build \
  && cmake --build . --config Release -- "-j$(nproc)"

FROM node:12-alpine as build_web
WORKDIR /app
COPY package-lock.json .
COPY package.json .
RUN npm ci
COPY public public
COPY src src
COPY rollup.config.js .
COPY .eslintrc.json .
COPY tsconfig.json .
COPY --from=build_nts /app/build/nts.wasm public/build/nts.wasm
COPY --from=build_nts /app/build/nts.js src/nts.js
RUN npm run build:app

FROM svenstaro/miniserve as serve
WORKDIR /app
COPY --from=build_web /app/public .
EXPOSE 80
CMD [ ".", "--index", "index.html", "-p", "80" ]
