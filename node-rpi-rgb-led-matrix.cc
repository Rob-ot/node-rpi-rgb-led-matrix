// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
//
// This code is public domain
// (but note, that the led-matrix library this depends on is GPL v2)

#include "led-matrix.h"
#include <unistd.h>
#include <math.h>
#include <stdio.h>

#include <nan.h>
#include <errno.h>

using namespace v8;
using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

Canvas *canvas;
GPIO io;

NAN_METHOD(start) {
  int rows      = args[0]->IntegerValue();
  int columns   = args[1]->IntegerValue();
  int chain     = args[2]->IntegerValue();
  int parallel  = args[3]->IntegerValue();
  canvas = new RGBMatrix(&io, rows, columns, chain, parallel);
  NanReturnUndefined();
}

NAN_METHOD(stop) {
  canvas->Clear();
  delete canvas;
  NanReturnUndefined();
}


NAN_METHOD(fill) {
  int r = args[0]->IntegerValue();
  int g = args[1]->IntegerValue();
  int b = args[2]->IntegerValue();
  canvas->Fill(r, g, b);
  NanReturnUndefined();
}

NAN_METHOD(setPixel) {
  int x = args[0]->IntegerValue();
  int y = args[1]->IntegerValue();
  int r = args[2]->IntegerValue();
  int g = args[3]->IntegerValue();
  int b = args[4]->IntegerValue();
  canvas->SetPixel(x, y, r, g, b);
  NanReturnUndefined();
}

NAN_METHOD(clear) {
  canvas->Clear();
  NanReturnUndefined();
}

void init(v8::Handle<v8::Object> exports) {

  exports->Set(NanNew("start"), NanNew<FunctionTemplate>(start)->GetFunction());
  exports->Set(NanNew("stop"), NanNew<FunctionTemplate>(stop)->GetFunction());
  exports->Set(NanNew("fill"), NanNew<FunctionTemplate>(fill)->GetFunction());
  exports->Set(NanNew("setPixel"), NanNew<FunctionTemplate>(setPixel)->GetFunction());
  exports->Set(NanNew("clear"), NanNew<FunctionTemplate>(clear)->GetFunction());

  io.Init();
}

NODE_MODULE(rpi_rgb_led_matrix, init);
