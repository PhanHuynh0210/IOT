# import subprocess

# input_file = "input.mp4"
# output_file = "output_compressed.mp4"

# command = [
#     "ffmpeg",
#     "-i", input_file,
#     "-vcodec", "libx264",   # codec nén phổ biến
#     "-crf", "28",           # chất lượng (18-28, càng lớn càng nhẹ)
#     "-preset", "fast",      # tốc độ encode
#     "-acodec", "aac",
#     "-b:a", "128k",
#     output_file
# ]

# subprocess.run(command)
import subprocess

input_file = "input.mp4"
output_file = "cut.mp4"

start_time = "00:00:45"   # bắt đầu (hh:mm:ss)
duration = "00:03:17"     # độ dài

subprocess.run([
    "ffmpeg",
    "-ss", start_time,
    "-i", input_file,
    "-t", duration,
    "-c", "copy",          # ⚡ không encode lại
    output_file
])