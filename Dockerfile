FROM gcc:7.3.0

COPY . /usr/src/peladen
WORKDIR /usr/src/peladen
RUN make

EXPOSE 8080
CMD ["./bin/peladen"]
