#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
拆分数学.md文件，提取代码块到独立的.cpp文件
"""

import re
import os
from pathlib import Path

def format_code(code):
    """格式化代码：去掉大括号换行，将 { 和 } 放在同一行"""
    lines = code.split('\n')
    formatted = []
    i = 0
    
    while i < len(lines):
        line = lines[i].rstrip()
        stripped = line.strip()
        
        # 跳过空行（但保留必要的空行）
        if not stripped:
            formatted.append('')
            i += 1
            continue
        
        # 如果当前行是独立的 {，尝试与上一行合并
        if stripped == '{':
            if formatted and formatted[-1].strip():
                prev_line = formatted[-1].rstrip()
                # 如果上一行有注释，需要处理注释位置
                if '//' in prev_line:
                    # 将注释移到 { 之前
                    comment_pos = prev_line.find('//')
                    main_part = prev_line[:comment_pos].rstrip()
                    comment = prev_line[comment_pos:]
                    formatted[-1] = main_part + ' ' + comment + ' {'
                elif not prev_line.endswith('{') and not prev_line.endswith(';') and not prev_line.endswith(':'):
                    # 合并到上一行
                    formatted[-1] = prev_line + ' {'
                else:
                    formatted.append(stripped)
                i += 1
                continue
        
        # 如果当前行是独立的 }，检查下一行是否是 else/catch
        if stripped == '}':
            if i + 1 < len(lines):
                next_stripped = lines[i + 1].strip()
                if next_stripped.startswith('else') or next_stripped.startswith('catch'):
                    formatted.append(stripped + ' ' + next_stripped)
                    i += 2
                    continue
        
        # 如果当前行以 { 结尾，检查下一行是否可以直接合并
        if line.endswith('{') and i + 1 < len(lines):
            next_line = lines[i + 1].strip()
            # 如果下一行是空的或者是注释，不合并
            if next_line and not next_line.startswith('//'):
                # 检查下一行是否只是 {
                if next_line == '{':
                    # 跳过下一行的 {
                    i += 1
                    continue
        
        formatted.append(line)
        i += 1
    
    # 再次处理：合并函数定义后的 {
    result = []
    i = 0
    while i < len(formatted):
        line = formatted[i]
        stripped = line.strip()
        
        # 检查是否是函数/结构体/类定义行，且下一行是 {
        if (stripped and not stripped.endswith('{') and not stripped.endswith(';') and 
            i + 1 < len(formatted) and formatted[i + 1].strip() == '{'):
            # 检查是否有注释
            if '//' in line:
                comment_pos = line.find('//')
                main_part = line[:comment_pos].rstrip()
                comment = line[comment_pos:]
                result.append(main_part + ' ' + comment + ' {')
            else:
                result.append(line + ' {')
            i += 2  # 跳过下一行的 {
            continue
        
        result.append(line)
        i += 1
    
    return '\n'.join(result)

def sanitize_filename(name):
    """清理文件名，移除非法字符"""
    # 移除 markdown 格式标记
    name = re.sub(r'\*\*', '', name)
    name = re.sub(r'<[^>]+>', '', name)
    name = re.sub(r'!\[.*?\]\(.*?\)', '', name)
    # 移除 LaTeX 图片标记
    name = re.sub(r'!\[image\]\([^\)]+\)', '', name)
    # 移除特殊字符
    name = re.sub(r'[<>:"/\\|?*]', '_', name)
    name = re.sub(r'\s+', '_', name.strip())
    name = re.sub(r'_+', '_', name)  # 多个下划线合并为一个
    name = name.strip('_')  # 移除首尾下划线
    return name or "unnamed"

def split_markdown_file(input_file, output_dir):
    """拆分markdown文件"""
    print(f"读取文件: {input_file}")
    with open(input_file, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 创建输出目录
    output_path = Path(output_dir)
    output_path.mkdir(exist_ok=True)
    code_dir = output_path / "code"
    code_dir.mkdir(exist_ok=True)
    
    # 按 ## 级别拆分
    sections = []
    lines = content.split('\n')
    current_section = []
    current_title = None
    code_counter = {}  # 用于计数每个章节的代码块
    
    i = 0
    while i < len(lines):
        line = lines[i]
        
        # 检查是否是 ## 级别的标题（不是 ###）
        if line.startswith('## ') and not line.startswith('###'):
            # 保存上一个section
            if current_section:
                sections.append((current_title, '\n'.join(current_section)))
            
            # 开始新的section
            current_title = line[3:].strip()
            current_section = [line]
            if current_title not in code_counter:
                code_counter[current_title] = 0
            i += 1
            continue
        
        # 检查是否是代码块开始
        if line.strip() == '```cpp':
            # 增加计数器
            if current_title not in code_counter:
                code_counter[current_title] = 0
            code_counter[current_title] += 1
            cnt = code_counter[current_title]
            
            code_content = []
            i += 1
            
            # 收集代码内容
            while i < len(lines) and lines[i].strip() != '```':
                code_content.append(lines[i])
                i += 1
            
            if code_content:
                code_text = '\n'.join(code_content)
                formatted_code = format_code(code_text)
                
                # 生成代码文件名
                if current_title:
                    code_filename = sanitize_filename(current_title)
                else:
                    code_filename = "unnamed"
                
                # 如果有多个代码块，添加序号
                if cnt > 1:
                    code_filename += f"_{cnt}"
                
                code_file = code_dir / f"{code_filename}.cpp"
                
                # 确保文件名唯一
                counter = 1
                original_code_file = code_file
                while code_file.exists():
                    code_file = code_dir / f"{code_filename}_{counter}.cpp"
                    counter += 1
                
                with open(code_file, 'w', encoding='utf-8') as cf:
                    cf.write(formatted_code)
                print(f"  提取代码: {code_file.name}")
                
                # 在markdown中替换为引用
                current_section.append("```cpp")
                current_section.append(f"// 代码已提取到: code/{code_file.name}")
                current_section.append("```")
            
            if i < len(lines):
                i += 1
            continue
        
        current_section.append(line)
        i += 1
    
    # 保存最后一个section
    if current_section:
        sections.append((current_title, '\n'.join(current_section)))
    
    # 写入拆分后的文件
    for title, content in sections:
        if not title:
            title = "未命名章节"
        
        filename = sanitize_filename(title) + ".md"
        filepath = output_path / filename
        
        # 确保文件名唯一
        counter = 1
        original_filepath = filepath
        while filepath.exists() and filepath != original_filepath:
            filepath = output_path / f"{sanitize_filename(title)}_{counter}.md"
            counter += 1
        
        # 添加标题（如果内容中没有）
        if not content.strip().startswith('#'):
            output_content = f"# {title}\n\n{content}"
        else:
            output_content = content
        
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(output_content)
        
        print(f"创建文件: {filepath.name}")
    
    print(f"\n完成! 共拆分 {len(sections)} 个章节，提取 {sum(code_counter.values())} 个代码文件")

if __name__ == '__main__':
    input_file = '数学.md'
    output_dir = '数学_split'
    
    split_markdown_file(input_file, output_dir)
