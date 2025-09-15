# render.py
from jinja2 import Environment, FileSystemLoader
import os

def render_template():
    # 1. 设置模板目录
    template_dir = 'templates'
    loader = FileSystemLoader(template_dir)
    env = Environment(loader=loader)

    # 2. 加载模板
    template = env.get_template('welcome.jinja')

    # 3. 定义数据（上下文）
    context = {
        'name': 'alice',
        'is_premium': True,
        'skills': ['python', 'javascript', 'git', 'docker']
    }

    # 4. 渲染模板
    output = template.render(**context)

    return output

if __name__ == '__main__':
    result = render_template()
    print(result)