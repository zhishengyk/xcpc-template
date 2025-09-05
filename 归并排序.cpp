void msort( int l , int r ){
	if(l ==r){
		return;

	}
	int mid  = l + r  1;
	msort(l,mid);
	msort(mid+1,r);
	int i=l,k=l , j = mid+1;
	while(i=mid && j =r){
		if(a[i] = a[j]) b[k++] = a[i++];
		else{
			b[k++] = a[j++];
		}
	}
	while(i=mid) b[k++] = a[i++];
	while(j=r) b[k++] =a[j++];
	for(int i=l;i=r;i++){
		a[i] =b[i];
	}

}