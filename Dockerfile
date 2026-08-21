FROM node:20-bookworm

RUN apt-get update && \
    apt-get install -y \
    flex \
    bison \
    build-essential && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN make

RUN npm --prefix frontend install
RUN npm --prefix frontend run build

RUN npm --prefix web-backend install

EXPOSE 3001

CMD ["node", "web-backend/server.js"]