ARG	REGISTRY=docker.io
FROM	${REGISTRY}/i386/debian:bullseye

MAINTAINER Steve Markgraf <steve@steve-m.de>

RUN	apt-get update && \
	apt-get upgrade -y && \
	apt-get install -y --no-install-recommends \
		build-essential \
		make \
		flex \
		texinfo \
		autoconf && \
	apt-get clean
