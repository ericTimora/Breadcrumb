package com.example.timora.breadcrumb;

import android.content.IntentSender;
import android.location.Location;
import android.os.Bundle;
import android.support.design.widget.NavigationView;
import android.support.v4.app.FragmentActivity;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarActivity;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.location.LocationListener;
import com.google.android.gms.location.LocationRequest;
import com.google.android.gms.maps.CameraUpdate;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

import com.google.android.gms.common.api.GoogleApiClient;

import com.google.android.gms.location.LocationServices;

public class MapsActivity
        extends     AppCompatActivity
        implements  GoogleApiClient.ConnectionCallbacks,
                    GoogleApiClient.OnConnectionFailedListener,
                    LocationListener,
                    NavigationView.OnNavigationItemSelectedListener {

    private GoogleMap               mMap;
    private GoogleApiClient         mGoogleApiClient;
    private LocationRequest         mLocationRequest;
    private Toolbar                 mToolbar;
    private NavigationView          mDrawer;
    private DrawerLayout            mDrawerLayout;
    private ActionBarDrawerToggle   mDrawerToggle;

    private final static int CONNECTION_FAILURE_RESOLUTION_REQUEST = 9000;
    public static final String TAG = MapsActivity.class.getSimpleName();


    private void handleNewLocation(Location location) {
        Log.d(TAG, location.toString());

        LatLng mLatLng = new LatLng(location.getLatitude(), location.getLongitude());
        CameraUpdate mCameraUpdate = CameraUpdateFactory.newLatLngZoom(mLatLng, 14);
        mMap.animateCamera(mCameraUpdate);
    }

    private void initiateDrawer(){
        mDrawer         = (NavigationView) findViewById(R.id.main_drawer);
        mDrawerLayout   = (DrawerLayout) findViewById(R.id.drawer_layout);
        mToolbar        = (Toolbar) findViewById(R.id.toolbar_header);
        mDrawerToggle   = new ActionBarDrawerToggle(this, mDrawerLayout, mToolbar,
                          R.string.open_drawer, R.string.close_drawer);

        setSupportActionBar(mToolbar);
        mDrawer.setNavigationItemSelectedListener(this);
        mDrawerLayout.setDrawerListener(mDrawerToggle);
        mDrawerToggle.syncState();
    }

    private void initiateMap(){
        setUpMapIfNeeded();
        mMap.setMyLocationEnabled(true);

        mGoogleApiClient =  new GoogleApiClient.Builder(this)
                            .addConnectionCallbacks(this)
                            .addOnConnectionFailedListener(this)
                            .addApi(LocationServices.API)
                            .build();

        mLocationRequest = LocationRequest.create()
                           .setPriority(LocationRequest.PRIORITY_HIGH_ACCURACY)
                           .setInterval(20000)
                           .setFastestInterval(10000);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maps);
        initiateDrawer();
        initiateMap();
    }
    @Override
    public boolean onCreateOptionsMenu(Menu menu){
        getMenuInflater().inflate(R.menu.menu_drawer, menu);
        return true;
    }
    @Override
    protected void onResume() {
        super.onResume();
        setUpMapIfNeeded();
        mGoogleApiClient.connect();
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (mGoogleApiClient.isConnected()) {
            LocationServices.FusedLocationApi.removeLocationUpdates(mGoogleApiClient, this);
            mGoogleApiClient.disconnect();
        }
    }

    private void setUpMapIfNeeded() {
        // Do a null check to confirm that we have not already instantiated the map.
        if (mMap == null) {
            // Try to obtain the map from the SupportMapFragment.
            mMap = ((SupportMapFragment) getSupportFragmentManager().findFragmentById(R.id.map))
                    .getMap();
            // Check if we were successful in obtaining the map.
            if (mMap != null) {
                // Do nothing for now
            }
        }
    }

    @Override
    public void onConnected(Bundle bundle) {
        Log.i(TAG, "Location services connected.");
        Location location = LocationServices.FusedLocationApi.getLastLocation(mGoogleApiClient);
        if (location == null) {
            LocationServices.FusedLocationApi.requestLocationUpdates(mGoogleApiClient, mLocationRequest, this);
        } else {
            handleNewLocation(location);
        }
    }

    @Override
    public void onConnectionSuspended(int i) {
        Log.i(TAG, "Location services suspended. Please reconnect.");
    }

    @Override
    public void onConnectionFailed(ConnectionResult connectionResult) {
        if (connectionResult.hasResolution()) {
            try {
                // Start an Activity that tries to resolve the error
                connectionResult.startResolutionForResult(this, CONNECTION_FAILURE_RESOLUTION_REQUEST);
            } catch (IntentSender.SendIntentException e) {
                e.printStackTrace();
            }
        } else {
            Log.i(TAG, "Location services connection failed with code " + connectionResult.getErrorCode());
        }
    }

    @Override
    public void onLocationChanged(Location location) {
        handleNewLocation(location);
    }

    @Override
    public boolean onNavigationItemSelected(MenuItem menuItem) {
       // menuItem.setChecked(true);
        return true;
    }
}
