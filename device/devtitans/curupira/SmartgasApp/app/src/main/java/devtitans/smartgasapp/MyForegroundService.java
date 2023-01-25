package devtitans.smartgasapp;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;

import androidx.annotation.Nullable;

import devtitans.smartgasmanager.SmartgasManager;

public class MyForegroundService extends Service {
    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {

        final String CHANNELID = "Foreground Service ID";
        NotificationChannel channel = new NotificationChannel(
                CHANNELID,
                CHANNELID,
                NotificationManager.IMPORTANCE_LOW
        );

        getSystemService(NotificationManager.class).createNotificationChannel(channel);
        Notification.Builder notification = new Notification.Builder(this, CHANNELID)
                .setContentText("Service is running")
                .setContentTitle("Service enabled")
                .setSmallIcon(R.drawable.ic_launcher_background);
        GasNotificationService gasNotificationService = new GasNotificationService();
        new Thread(
                new Runnable() {
                    @Override
                    public void run() {
                        while (true) {
                            Log.e("smartgas", "Foreground service is running...");
                            try {
                                int concentration = SmartgasManager.getInstance().getConcentration();
                                Log.d("smartgas", "concentration = " + concentration);
                                if (concentration > 2300) {
                                    Log.d("smartgas", "ALTA CONCENTRAÇÃO DE GÁS!!");
                                    gasNotificationService.showNotification(MyForegroundService.this, "PERIGO!!!!!!", "ALTA CONCENTRAÇÃO DE GÁS: "+concentration, intent, 1001);
                                } else {
                                    Log.d("smartgas", "Baixa concentração de gás");
                                    gasNotificationService.showNotification(MyForegroundService.this, "ATENÇÃO!", "CONCENTRAÇÃO DE GÁS: "+concentration, intent, 1001);

                                }
                            } catch (RemoteException e) {
                                e.printStackTrace();
                            }

                            try {
                                Thread.sleep(2000);
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }
                        }
                    }
                }
        ).start();

        startForeground(1001, notification.build());
        return super.onStartCommand(intent, flags, startId);
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }
}