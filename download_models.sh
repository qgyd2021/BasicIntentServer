#!/usr/bin/env bash

mkdir models && cd models || exit 1;

for model_name in basic_intent_cn_20230414 basic_intent_en_20230414 basic_intent_jp_20230414 basic_intent_vi_20230414
do
  wget -c "https://huggingface.co/qgyd2021/BasicIntentModels/resolve/main/${model_name}.zip"
  unzip "${model_name}.zip"
  rm "${model_name}.zip"
  rm -rf "${model_name}/*.ckpt"
  rm "${model_name}/pytorch_model.bin"
  rm "${model_name}/test_output.xlsx"
  rm -rf "${model_name}/vocabulary"
done
