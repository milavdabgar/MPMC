# GTU Paper Solution Generation Guidelines

Create simple GTU paper solutions using a systematic artifact-based approach for weak students who struggle with exams. I've uploaded a paper PDF.

## GUIDELINES FOR SOLUTION CREATION:

### 1. Artifact Organization

- Create complete paper solution in a single artifact with proper title: `[subject-code]-[season]-[year]-solution`
- When hitting message length limits, continue in new artifact labeled "Part 2", "Part 3", etc.
- First create the complete English version, then create the Gujarati version
- Example for English: `4341101-summer-2024-solution`
- Example for Gujarati: `4341101-summer-2024-solution.gu`

### 2. FORMAT for Solution

- **English Format**:
  * Question X(y): [text] (Marks: Z) 
  * Answer X(y): [answer] 
  * For OR questions: X(y OR)
- **Gujarati Format**:
  * પ્રશ્ન X(y): [text] (ગુણ: Z)
  * જવાબ X(y): [answer]
  * For OR questions: પ્રશ્ન X(y OR)

### 3. Content Requirements

- **Reduced word count** for very weak students - strictly follow these limits:
  * 3-mark questions: 50-60 words
  * 4-mark questions: 75-90 words
  * 7-mark questions: 125-150 words

### 4. Solution Structural Elements

1. Give utmost importance to **diagrams and tables**. Whenever a part of answer can be explained using diagrams and tables, use them instead of text.
2. Use **proper markdown syntax** for all formatting:
   - Use hyphen (`-`) or asterisk (`*`) for bullet points
   - For numbered lists, use proper markdown numbering
   - Use proper headings with hash symbols
3. Each bullet point should have **bold keywords** that help students memorize which keywords are key
4. Create memorable **mnemonics** to help students recall the answer
5. Create code as **minimal and simple** as possible, as weak students struggle with coding
6. For diagrams:
   - Use mermaid, SVG, or ASCII art that's compatible with pandoc and Hugo
   - Do not use image references or links
   - For circuit diagrams, ASCII art often works best
   - For flowcharts and architecture diagrams, mermaid is preferred

### 5. Gujarati Translation Guidelines

- Do NOT translate word-for-word; adapt the content culturally
- Use natural, conversational Gujarati as spoken by contemporary students
- Keep all technical terms in English (programming terms, keywords, etc.)
- Ensure the content flows naturally and doesn't sound like a direct translation
- Use transliteration in Gujarati script that feels familiar to modern-day Gujarati speakers
- Include all diagrams, tables, and visual elements in the Gujarati version identical to the English version
- Ensure both English and Gujarati versions present the same level of detail and content

I'll ask for solutions by typing: "Start" or "Question 1(a)" for the first "Next" for subsequent questions.
