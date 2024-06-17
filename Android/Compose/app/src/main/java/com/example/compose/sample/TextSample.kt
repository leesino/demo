package com.example.compose.sample


import android.util.Log
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.text.ClickableText
import androidx.compose.foundation.text.selection.SelectionContainer
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.Shadow
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.SpanStyle
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.buildAnnotatedString
import androidx.compose.ui.text.font.FontFamily
import androidx.compose.ui.text.font.FontStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.text.style.TextDecoration
import androidx.compose.ui.text.style.TextIndent
import androidx.compose.ui.text.style.TextOverflow
import androidx.compose.ui.text.withStyle
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.TextUnit
import androidx.compose.ui.unit.TextUnitType
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.em
import androidx.compose.ui.unit.sp
import com.example.compose.R

@Composable
fun TextSample1() {
    Text(text = "Hello World")
}

@Composable
fun TextSample2() {
    Text(text = stringResource(id = R.string.app_name))
}

@Composable
fun TextSample3() {
    Text(text = "Hello World", color = Color.Red)
}

@Composable
fun TextSample4() {
    Column {
        Text(text = "Hello World",
            fontSize = TextUnit(24f, TextUnitType.Sp))
        Text(text = "Hello World", fontSize = 16.sp)
        Text(text = "Hello World", fontSize = 10.em)
    }

}

@Composable
fun TextSample5() {
    Column {
        Text(text = "Hello World",)
        Text(text = "Hello World",
            fontStyle = FontStyle.Normal)
        Text(text = "Hello World",
            fontStyle = FontStyle.Italic)
    }
}

@Composable
fun TextSample6() {
    Column {
        Text(text = "Thin",
            fontWeight = FontWeight.Thin)
        Text(text = "Light",
            fontWeight = FontWeight.Light)
        Text(text = "Normal",
            fontWeight = FontWeight.Normal)
        Text(text = "SemiBold",
            fontWeight = FontWeight.SemiBold)
        Text(text = "Bold",
            fontWeight = FontWeight.Bold)
        Text(text = "ExtraBold",
            fontWeight = FontWeight.ExtraBold)
    }
}

@Composable
fun TextSample7() {
    Column {
        Text(text = "Hello World!")
        Text(text = "Hello World!",
            letterSpacing = 15.sp)
    }
}

@Composable
fun TextSample7_1(){
    Column {
        Text("Hello World", fontFamily = FontFamily.Serif)
        Text("Hello World", fontFamily = FontFamily.SansSerif)
    }
}

@Composable
fun TextSample8() {
    Column {
        Text(text = "Hello World!",
                textDecoration = TextDecoration.LineThrough)
        Text(text = "Hello World!",
            textDecoration = TextDecoration.Underline)
        Text(text = "Hello World!",
            textDecoration = TextDecoration.combine(
                listOf(
                    TextDecoration.LineThrough,
                    TextDecoration.Underline
                )
            ))
    }
}

@Composable
fun TextSample9() {
    Column {
        Text(text = "Start", modifier = Modifier.width(120.dp),
          textAlign = TextAlign.Start)
        Text(text = "Middle",modifier = Modifier.width(120.dp),
            textAlign = TextAlign.Center)
        Text(text = "End",modifier = Modifier.width(120.dp),
            textAlign = TextAlign.End)
        Text(text = "Justify Justify Justify Justify",
            modifier = Modifier.width(120.dp),
            textAlign = TextAlign.Justify)
    }
}

@Composable
fun TextSample10() {
    Column {
        Text(text = "Hello \nWorld!",
            modifier = Modifier.background(color = Color.Green))
        Text(text = "Hello \nWorld",
            modifier = Modifier.background(color = Color.Yellow),
            lineHeight = 25.sp)
    }
}

@Composable
fun TextSample11() {
    Column {
        Text(text = "Hello World!",
            maxLines = 1,
            modifier = Modifier.width(60.dp),
            overflow = TextOverflow.Ellipsis
        )
        Text(text = "Hello World!",
            maxLines = 1,
            modifier = Modifier.width(60.dp),
            overflow = TextOverflow.Clip
        )
        Text(text = "Hello World!",
            modifier = Modifier.width(60.dp),
            overflow = TextOverflow.Visible,
            maxLines = 1,
        )
    }
}

@Composable
fun TextSample12() {
    Text(
        text = "设置文字的样式",
        modifier = Modifier.width(100.dp),
        style = TextStyle(
            background = Color.White,
            shadow = Shadow(
                color = Color.Red,
                offset = Offset(5f, 5f),
                blurRadius = 10f
            ),
            textIndent = TextIndent(20.sp)
        )
    )
}

@Composable
fun TextSample13() {
    SelectionContainer{
        Text(text = "可复制的文字\n可复制的文字\n可复制的文字")
    }
}

@Composable
fun TextSample14() {
    Text(
        buildAnnotatedString {
            withStyle(style = SpanStyle(Color.Red)) {
                append("第一行\n")
            }
            withStyle(style = SpanStyle(Color.Green)) {
                append("第二行\n")
            }
            withStyle(style = SpanStyle(Color.Blue)) {
                append("第三行")
            }
        }
    )
}

@Composable
fun TextSample15() {
    ClickableText(
        buildAnnotatedString {
            withStyle(style = SpanStyle(Color.Red)) {
                append("第一行\n")
            }
            withStyle(style = SpanStyle(Color.Green)) {
                append("第二行\n")
            }
        }, onClick = { offset ->
            Log.d("TextSample", "offset:$offset")
        }
    )
}

@Composable
fun TextSample16() {
    val annotatedString = buildAnnotatedString {
        append("点击登录代表您知悉和同意")
        pushStringAnnotation("protocol", annotation = "https://xxx/protocol")
        withStyle(style = SpanStyle(Color.Blue)) {
            append("用户协议")
        }
        pop()
        append("和")
        pushStringAnnotation("privacy", annotation = "https://xxx/private")
        withStyle(style = SpanStyle(Color.Blue)) {
            append("隐私政策")
        }
        pop()
    }
    ClickableText(
        annotatedString, onClick = { offset ->
            annotatedString.getStringAnnotations("protocol", start = offset, end = offset)
                .firstOrNull()?.let { annotation ->
                    Log.d("TextSample", "点击了用户协议：${annotation.item}")
                }
            annotatedString.getStringAnnotations("privacy", start = offset, end = offset)
                .firstOrNull()?.let { annotation ->
                    Log.d("TextSample", "点击了隐私政策：${annotation.item}")
                }
        }
    )
}

@Preview
@Composable
fun TextSamplePreview() {
    TextSample7_1()
}





