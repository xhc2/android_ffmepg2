package com.example.xhc.android_ffmepg2;


import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.DialogInterface;

import android.os.Bundle;
import android.text.TextUtils;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;


public class BaseActivity extends AppCompatActivity {

    private ProgressDialog dialog;
//    private LoadProgressDialog progressDialog;


    protected void showDialog(String msg) {
        if (dialog == null) {
            dialog = new ProgressDialog(this);
        }
        dialog.setMessage(msg);
        dialog.show();
    }

    protected void dismissDialog() {
        if (dialog != null && dialog.isShowing()) {
            dialog.dismiss();
        }
    }

    protected void showToast(String msg) {
        Toast.makeText(this, msg, Toast.LENGTH_SHORT).show();
    }

    protected void showLoadPorgressDialog(String msg) {
//        if (progressDialog == null) {
//            progressDialog = new LoadProgressDialog(this, msg);
//        }
//        progressDialog.show();
    }

    protected void dismissLoadPorgressDialog() {
//        if (progressDialog != null && progressDialog.isShowing()) {
//            progressDialog.dismiss();
//        }
    }

    protected void setLoadPorgressDialogProgress(int progress) {
//        if (progressDialog != null && progressDialog.isShowing()) {
//            progressDialog.setProgress(progress);
//        }
    }


    protected void showAlertDialog(String title, String msg  , DialogInterface.OnClickListener positiveB) {
        AlertDialog.Builder builder= new AlertDialog.Builder(this);
        if(!TextUtils.isEmpty(title)){
            builder.setTitle(title);
        }
        if(!TextUtils.isEmpty(msg)){
            builder.setMessage(msg);
        }
//        builder.setIcon(R.mipmap.logo);
        builder.setNegativeButton("取消", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
            }
        });
        builder.setPositiveButton("确定" , positiveB);
        AlertDialog dialog = builder.create();
        dialog.show();
    }




    @Override
    protected void onDestroy() {
        super.onDestroy();
        dismissDialog();
    }
}
