import os
# 强制指定 D 盘
os.environ["HF_HOME"] = "/mnt/d/AI_Work/hf_cache"
# 强制使用国内镜像 (解决下载没反应/卡住的问题)
os.environ["HF_ENDPOINT"] = "https://hf-mirror.com"

from transformers import AutoModelForCausalLM, AutoTokenizer

print("🚀 正在开始下载到 D 盘，请不要关闭窗口...")
# 这两行会触发下载
AutoModelForCausalLM.from_pretrained("microsoft/bitnet-b1.58-2B-4T-bf16")
AutoTokenizer.from_pretrained("microsoft/bitnet-b1.58-2B-4T-bf16")
print("✅ 下载完成！")