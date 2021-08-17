#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from flask import Flask
import os
import sys

app = Flask(__name__)

from app import routes, database
