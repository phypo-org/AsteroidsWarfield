#!/bin/bash

PROG_NAME=AsteroidsWarfield
PROG_EXE=AWF.exe
PROG_PATH=../Debug/${PROG_EXE}
DATA=../Run/data
CONFIG=../Run/${PROG_NAME}.ini


DEST=${1}/${PROG_NAME}
DEST_USR=${1}/${PROG_NAME}/usr

DEST_BIN=${DEST}/usr/bin
DEST_LIB=${DEST}/usr/lib
DEST_SHR=${DEST}/usr/share
DEST_DAT=${DEST}/usr/share/data
DEST_CFG=${DEST}/usr/share

# a enlever
# rm -rf  ${DEST_BIN} ${DEST_IMG} ${DEST_CFG}  ${DEST_LIB}

mkdir -p ${1} ${DEST}
mkdir -p ${DEST_USR} ${DEST_BIN} ${DEST_LIB} ${DEST_SHR} ${DEST_DAT} ${DEST_CFG} 


install_prog_lib.sh ${PROG_PATH} ${DEST_LIB}


cp -f ${PROG_PATH}  ${DEST_BIN}
cp -rp ${DATA}/*    ${DEST_DAT}

cp -rp ${CONFIG}    ${DEST_CFG}


cp AppRun ${PROG_NAME}.desktop ${PROG_NAME}.png $DEST
