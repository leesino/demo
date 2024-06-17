package com.example.compose.ui.theme.sample


import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.size
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Person
import androidx.compose.material3.Icon
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.BlendMode
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.ColorFilter
import androidx.compose.ui.graphics.ImageBitmap
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.res.imageResource
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import coil.compose.AsyncImage
import com.example.compose.R


@Composable
fun IconSample() {
    Column {
        Icon(imageVector = Icons.Default.Person,
            contentDescription = null,
            modifier = Modifier.size(80.dp),
            tint = Color.Red)
        Icon(
            painter = painterResource(
                id = R.drawable.ic_launcher_foreground),
            contentDescription = null,
            tint = Color.Green
        )
    }
}

@Composable
fun ImageSample(){
    Column {
        Image(
            painter = painterResource(id = R.drawable.ic_launcher_foreground),
            contentDescription = null,
            contentScale = ContentScale.Inside,
            colorFilter = ColorFilter.tint(Color.Green, blendMode = BlendMode.Color)
        )
    }
}

@Composable
fun AsyncImageSample(){
    AsyncImage(
        model = "https://image.baidu.com/search/detail?ct=503316480&z=undefined&tn=baiduimagedetail&ipn=d&word=jetpack&step_word=&lid=12295549488477976543&ie=utf-8&in=&cl=2&lm=-1&st=undefined&hd=undefined&latest=undefined&copyright=undefined&cs=4236239468,1755090028&os=873663976,3867994079&simid=3369909829,317826972&pn=1&rn=1&di=7360350738658099201&ln=1170&fr=&fmq=1718587882095_R&fm=&ic=undefined&s=undefined&se=&sme=&tab=0&width=undefined&height=undefined&face=undefined&is=0,0&istype=0&ist=&jit=&bdtype=0&spn=0&pi=0&gsm=1e&objurl=https%3A%2F%2Fimg.zhilepin.com%2Fueditor%2Fimage%2F20151110%2F1447145638988009.jpg&rpstart=0&rpnum=0&adpicid=0&nojc=undefined&dyTabStr=MCwxLDMsMiw2LDQsNSw3LDgsOQ%3D%3D",
        contentDescription = null,
    )
}

@Preview
@Composable
fun IconSamplePreview() {
    AsyncImageSample()
}
