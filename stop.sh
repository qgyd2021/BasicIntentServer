#!/usr/bin/env bash

kill -9 `ps -aef | grep 'BasicIntentServer' | grep -v grep | awk '{print $2}'`

